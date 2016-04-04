/*
 * CANController.cpp
 *
 * Copyright 2011, 2012 Germaneers GmbH
 * Copyright 2011, 2012 Hubert Denkmair (hubert.denkmair@germaneers.com)
 *
 * This file is part of libopenstella.
 *
 * libopenstella is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * libopenstella is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libopenstella.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../kybos.h"

#include GENERATE_HAL_INCLUDE(STM32_FAMILY,)
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _rcc)
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _rcc_ex)
#include GENERATE_HAL_INCLUDE(STM32_FAMILY, _can)

#include "CANController.h"
#include <string.h>
#include "../OS/Mutex.h"

#ifdef HAL_CAN_MODULE_ENABLED

CANController::CANController(CANBus::channel_t channel) :
	Task(0, 160),
	_channel(channel),
	_observerMutex(),
	_lastMessageReceivedTimestamp(0),
	_silent(false),
	_timeToWaitForFreeMob(100),
	_bitrate(CANBus::bitrate_500kBit),
	_pool(20)
{
	static const char* tasknames[CANBus::num_channels] = {
#ifdef HAS_CAN_CHANNEL_1
			"can1"
#endif
#ifdef HAS_CAN_CHANNEL_2
			"can2",
#endif
	 };

	setTaskName(tasknames[channel]);

	_observers = createObserverListFragment();
}

CANController::observer_list_t *CANController::createObserverListFragment()
{
	CANController::observer_list_t *result = new CANController::observer_list_t;
	memset(result, 0, sizeof(CANController::observer_list_t));
	return result;
}

void CANController::setBitrate(CANBus::bitrate_t bitrate)
{
	uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();

	switch (pclk1){
	case 48000000:
		_handle.Init.BS1 = CAN_BS1_11TQ; /* Set Sampling Point to 75.0 percent */
		_handle.Init.BS2 = CAN_BS2_4TQ;  /* Set Sampling Point to 75.0 percent */
		_handle.Init.SJW = CAN_SJW_2TQ;  /* Values 1-4 allowed */
		switch (bitrate) {
		case 100000:
		case 125000:
		case 250000:
		case 500000:
		case 1000000:
			_handle.Init.Prescaler = pclk1/(bitrate*(1+11+4)); // Sync == 1Tq, BS1 == 11Tq, BS2 == 4Tq
			break;
		default:
			while (1) { ; }
		}

		break;
	case 45000000:
		_handle.Init.BS1 = CAN_BS1_10TQ; /* Set Sampling Point to 73.3 percent */
		_handle.Init.BS2 = CAN_BS2_4TQ;  /* Set Sampling Point to 73.3 percent */
		_handle.Init.SJW = CAN_SJW_2TQ;  /* Values 1-4 allowed */
		switch (bitrate) {
		case 100000:
		case 125000:
		case 250000:
		case 500000:
		case 1000000:
			_handle.Init.Prescaler = pclk1/(bitrate*(1+10+4)); // Sync == 1Tq, BS1 == 10Tq, BS2 == 4Tq
			break;
		default:
			while (1) { ; }
		}

		break;
	case 42000000:
		_handle.Init.BS1 = CAN_BS1_15TQ; /* Set Sampling Point to 76.2 percent */
		_handle.Init.BS2 = CAN_BS2_5TQ;  /* Set Sampling Point to 76.2 percent */
		_handle.Init.SJW = CAN_SJW_2TQ;  /* Values 1-4 allowed */
		switch (bitrate) {
		case 100000:
		case 125000:
		case 250000:
		case 500000:
		case 1000000:
			_handle.Init.Prescaler = pclk1/(bitrate*(1+15+5)); // Sync == 1Tq, BS1 == 10Tq, BS2 == 4Tq
			break;
		default:
			while (1) { ; }
		}
		break;
	default: // not implemented yet!
		while (1) { ; }
	}



}

void CANController::setup(CANBus::bitrate_t bitrate, GPIOPin rxpin, GPIOPin txpin)
{

	_handle.State = HAL_CAN_STATE_RESET;


	_handle.Init.RFLM = DISABLE;
	_handle.Init.TXFP = DISABLE;
	_handle.Init.TTCM = DISABLE;
	_handle.Init.AWUM = DISABLE;
	_handle.Init.NART = DISABLE;
	_handle.Init.ABOM = ENABLE;
	_handle.Init.Mode = CAN_MODE_NORMAL;

	_handle.pRxMsg = &_rxMsg;
	_handle.pTxMsg = &_txMsg;


	setBitrate(bitrate);

	_handle.Lock = HAL_UNLOCKED;

	switch(_channel) {
#if defined HAS_CAN_CHANNEL_2
	case CANBus::channel_1:
		_handle.Instance = CAN1;
		rxpin.mapAsCAN1RX();
		txpin.mapAsCAN1TX();
		__HAL_RCC_CAN1_CLK_ENABLE();
		break;
	case CANBus::channel_2:
		_handle.Instance = CAN2;
		rxpin.mapAsCAN2RX();
		txpin.mapAsCAN2TX();
		__HAL_RCC_CAN1_CLK_ENABLE(); // For CAN2, we need CAN1 clock also!
		__HAL_RCC_CAN2_CLK_ENABLE();
		break;
#elif defined HAS_CAN_CHANNEL_1
	case CANBus::channel_1:
		_handle.Instance = CAN;
		rxpin.mapAsCAN1RX();
		txpin.mapAsCAN1TX();
		__HAL_RCC_CAN1_CLK_ENABLE();
		break;
#endif
	default:
		while(1) {;}
	}



	HAL_CAN_Init(&_handle);

	CAN_FilterConfTypeDef CAN_FilterInitStructure;

	CAN_FilterInitStructure.FilterNumber=1;
	CAN_FilterInitStructure.FilterMode=CAN_FILTERMODE_IDMASK;
	CAN_FilterInitStructure.FilterScale=CAN_FILTERSCALE_16BIT;
	CAN_FilterInitStructure.FilterIdHigh=0x0000;
	CAN_FilterInitStructure.FilterIdLow=0x0000;
	CAN_FilterInitStructure.FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.FilterActivation=ENABLE;
	CAN_FilterInitStructure.BankNumber = 1;
	HAL_CAN_ConfigFilter(&_handle, &CAN_FilterInitStructure);

#if defined(STM32F0)
	HAL_NVIC_SetPriority(CEC_CAN_IRQn, 3, 0); /* Set CAN1 Rx interrupt priority to 3-0 */
	HAL_NVIC_EnableIRQ(CEC_CAN_IRQn); /* Enable CAN1 Rx Interrupt */
#elif defined(STM32F4)
#error "NOT IMPLEMENTED YET"
#else
#error "NOT IMPLEMENTED YET"
#endif

	__HAL_CAN_ENABLE_IT(&_handle, CAN_IT_FMP0); /* Enable 'message pending in FIFO0' interrupt */

	this->enable();

}

void CANController::execute()
{
	while(1) {
		uint8_t num;

		while (_usedSwMobs.receive(&num, 0)) {
			_lastMessageReceivedTimestamp = getTime();
			notifyObservers(&_rxMsgBuf[num]);
			_freeSwMobs.sendToBack(num);
		}


		uint32_t timeToWait = sendCyclicCANMessages();
		if (timeToWait>100) timeToWait = 100;

		_usedSwMobs.peek(&num, timeToWait);

	}
}

void CANController::enable()
{
	run();
}

void CANController::disable()
{
	stop();
}


CANBus::error_counters_t CANController::getErrorCounters()
{
	CANBus::error_counters_t result = { 0, 0, false};

	// TODO FIXME: to be implemented
	return result;
}


bool CANController::sendMessage(CANMessage *msg)
{
	MutexGuard guard(&_sendMessageMutex);

	if (_silent) return true;

	_handle.pTxMsg->DLC = msg->dlc;
	_handle.pTxMsg->IDE = msg->isExtendedId()?CAN_ID_EXT:CAN_ID_STD;
	_handle.pTxMsg->RTR = msg->isRemoteFrame()?CAN_RTR_REMOTE:CAN_RTR_DATA;
	memcpy(_handle.pTxMsg->Data, msg->data, msg->dlc);
	if (_handle.pTxMsg->IDE) {
		_handle.pTxMsg->ExtId = msg->id;
	}
	else {
		_handle.pTxMsg->StdId = msg->id;
	}

	HAL_StatusTypeDef status = HAL_CAN_Transmit(&_handle, _timeToWaitForFreeMob);

	return (status == HAL_OK);
}

CANController *CANController::_controllers[CANBus::num_channels] = {0,};
CANController *CANController::get(CANBus::channel_t channel)
{
	static Mutex _mutex;
	MutexGuard guard(&_mutex);

	if (!_controllers[channel])
	{
		switch (channel) {

#ifdef HAS_CAN_CHANNEL_1
			case CANBus::channel_1:
				break;
#endif

#ifdef HAS_CAN_CHANNEL_2
			case CANBus::channel_2:
				break;
#endif

			default:
				while(1);
				break;
		}
		_controllers[channel] = new CANController(channel);
	}

	return _controllers[channel];
}

void CANController::notifyObservers(CanRxMsgTypeDef *msgHndle)
{
	MutexGuard guard(&_observerMutex);

	observer_list_t *list = _observers;
	while (list != 0) {
		for (int i=0; i<observer_list_length; i++) {
			observer_list_entry_t *entry = &list->entries[i];
			if (!entry->observer) continue;

			uint32_t canid = ((msgHndle->IDE)==CAN_ID_EXT)?msgHndle->ExtId:msgHndle->StdId;
			if ( (canid & entry->mask) == (entry->can_id & entry->mask) )
			{
				// match. notify the observer.
				CANMessage *msg = _pool.getMessage();
				if (msg) {
					msg->_flags  = msgHndle->IDE | msgHndle->RTR;
					msg->_receivingController = this;
					msg->id = canid;
					msg->dlc = msgHndle->DLC;
					memcpy(msg->data, msgHndle->Data, sizeof(msg->data));


					if (!entry->observer->notifyCANMessage(msg)) {
						_pool.returnMessage(msg);
					}
				}
			}
		}
		list = list->next;
	}

}


void CANController::returnMessageToPool(CANMessage *obj)
{
	_pool.returnMessage(obj);
}

bool CANController::registerObserver(CANObserver *observer)
{
	return registerObserver(observer, 0, 0);
}

bool CANController::registerObserver(CANObserver *observer, int32_t can_id, uint32_t mask)
{
	MutexGuard guard(&_observerMutex);

	// don't register if same observer on same object is already installed
	observer_list_t *list = _observers;
	while (list != 0) {
		for (int i=0; i<observer_list_length; i++) {
			if ( (list->entries[i].observer == observer)
			  && (list->entries[i].can_id == can_id)
			  && (list->entries[i].mask == mask)
			) {
				return true; // already registered
			}
		}
		list = list->next;
	}

	list = _observers;
	while (list != 0) {
		for (int i=0; i<observer_list_length; i++) {
			if (list->entries[i].observer==0) { // found an empty slot
				list->entries[i].observer = observer;
				list->entries[i].can_id = can_id;
				list->entries[i].mask = mask;
				return true;
			}
		}
		if (list->next==0) {
			list->next = createObserverListFragment();
		}
		list = list->next;
	}
	return false;
}

int CANController::unregisterObserver(CANObserver *observer)
{
	MutexGuard guard(&_observerMutex);

	int result = 0;

	for (observer_list_t *list=_observers; list!=0; list=list->next) {
		for (int i=0; i<observer_list_length; i++) {
			if (list->entries[i].observer==observer) {
				list->entries[i].observer = 0;
				result++;
			}
		}
	}

	return result;
}

int CANController::unregisterObserver(CANObserver *observer, int32_t can_id, uint32_t mask)
{
	MutexGuard guard(&_observerMutex);

	int result = 0;
	for (observer_list_t *list=_observers; list!=0; list=list->next) {
		for (int i=0; i<observer_list_length; i++) {
			if (
					(list->entries[i].observer==observer)
				&& ((list->entries[i].can_id & mask) == (can_id & mask))
				&& ((list->entries[i].mask) == mask)
			) {
				list->entries[i].observer = 0;
				result++;
			}
		}
	}

	return result;
}

void CANController::registerCyclicMessage(CANCyclicMessage *cmsg)
{
	_cyclicMessages.addItem(cmsg);
}

void CANController::unregisterCyclicMessage(CANCyclicMessage *cmsg)
{
	_cyclicMessages.removeItem(cmsg);
}

void CANController::registerCyclicMessage(CANMessage *msg, uint32_t interval)
{
	CANCyclicMessage *cmsg = new CANCyclicMessage(msg, interval);
	_cyclicMessages.addItem(cmsg);
}

void CANController::unregisterCyclicMessage(CANMessage *msg)
{
	_cyclicMessages.lock();
	for (auto *list = _cyclicMessages._firstFragment; list!=0; list = list->next)
	{
		for (int i=0; i<_cyclicMessages._fragmentSize; i++) {
			CANCyclicMessage *item = list->items[i];
			if ((item!=0) && (item->_msg==msg)) {
				list->items[i] = 0;
			}
		}
	}
	_cyclicMessages.unlock();
}

uint32_t CANController::sendCyclicCANMessages()
{
	_cyclicMessages.lock();

	uint32_t now = getTime();
	uint32_t timestamp_next_call = now + 1000;

	for (auto *list = _cyclicMessages._firstFragment; list!=0; list = list->next)
	{
		for (int i=0; i<_cyclicMessages._fragmentSize; i++) {
			CANCyclicMessage *item = list->items[i];
			if (item!=0) {
				if (!item->isEnabled()) continue;

				if (item->_timestamp_next_send <= now) {
					item->send(this);
				}

				while (item->_timestamp_next_send <= now) {
					item->_timestamp_next_send += item->_interval;
				}

				if (timestamp_next_call > item->_timestamp_next_send) {
					timestamp_next_call = item->_timestamp_next_send;
				}

			}
		}

	}

	_cyclicMessages.unlock();
	return timestamp_next_call - now;
}

bool CANController::sendMessage(uint32_t id)
{
	CANMessage msg(id,0);
	return sendMessage(&msg);
}


bool CANController::sendMessage(uint32_t id, uint8_t b1)
{
	CANMessage msg(id, 1);
	msg.data[0] = b1;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2)
{
	CANMessage msg(id,2);
	msg.data[0] = b1;
	msg.data[1] = b2;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3)
{
	CANMessage msg(id,3);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
	CANMessage msg(id,4);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	msg.data[3] = b4;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5)
{
	CANMessage msg(id,5);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	msg.data[3] = b4;
	msg.data[4] = b5;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6)
{
	CANMessage msg(id,6);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	msg.data[3] = b4;
	msg.data[4] = b5;
	msg.data[5] = b6;
	return sendMessage(&msg);
}



bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7)
{
	CANMessage msg(id,7);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	msg.data[3] = b4;
	msg.data[4] = b5;
	msg.data[5] = b6;
	msg.data[6] = b7;
	return sendMessage(&msg);
}

bool CANController::sendMessage(uint32_t id, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7, uint8_t b8)
{
	CANMessage msg(id,8);
	msg.data[0] = b1;
	msg.data[1] = b2;
	msg.data[2] = b3;
	msg.data[3] = b4;
	msg.data[4] = b5;
	msg.data[5] = b6;
	msg.data[6] = b7;
	msg.data[7] = b8;
	return sendMessage(&msg);
}


uint32_t CANController::getTimeSinceLastReceivedMessage()
{
	return getTime() - _lastMessageReceivedTimestamp;
}

bool CANController::sendMessage(uint32_t id, uint8_t dlc, const void* const ptr)
{
	//uint8_t *data = (uint8_t *) ptr;

	if (dlc > 8) dlc = 8;
	CANMessage msg(id, dlc);
	if (dlc > 0) {
		memcpy(msg.data, ptr, dlc);
	}
	return sendMessage(&msg);
}

void CANController::handleRx(void)
{
	uint8_t rxBufId;
	_freeSwMobs.receiveFromISR(&rxBufId);
	memcpy (&_rxMsgBuf[rxBufId], _handle.pRxMsg, sizeof(CanRxMsgTypeDef));
	_usedSwMobs.sendToBackFromISR(rxBufId);
	__HAL_CAN_ENABLE_IT(&_handle, CAN_IT_FMP0); /* Enable 'message pending in FIFO0' interrupt */
}

void CANController::setSilent(bool beSilent)
{
	_silent = beSilent;
}

void CANController::setTimeToWaitForFreeMob(uint32_t ms_to_wait)
{
	_timeToWaitForFreeMob = ms_to_wait;
}


extern "C" {

#ifdef STM32F0
void CEC_CAN_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&CANController::_controllers[0]->_handle);
}
#endif

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *hcan)
{
	UNUSED(hcan);
	CANController::_controllers[0]->handleRx();

}

}

#endif // HAL_CAN_MODULE_ENABLED



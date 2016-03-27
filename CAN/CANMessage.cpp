/*
 * CANMessage.cpp
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

#include "CANMessage.h"
#include "CANController.h"

#include <string.h>

CANMessage::CANMessage(uint32_t id, uint8_t dlc)
  : _flags(0), _receivingController(0), id(id), dlc(dlc)
{
	memset(data, 0, 8);
	setExtendedId(id>=0x800);
}


bool CANMessage::isExtendedId()
{
	return (_flags & CAN_ID_EXT) != 0;
}

void CANMessage::setExtendedId(bool extended)
{
	if (extended) {
		_flags |= CAN_ID_EXT;
	} else {
		_flags &= ~CAN_ID_EXT;
	}
}

bool CANMessage::isRemoteFrame()
{
	return (_flags & CAN_RTR_REMOTE) != 0;
}

void CANMessage::setRemoteFrame(bool remote)
{
	if (remote) {
		_flags |= CAN_RTR_REMOTE;
	} else {
		_flags &= ~CAN_RTR_REMOTE;
	}
}

CANController *CANMessage::getReceivingController() const
{
    return _receivingController;
}

CAN::channel_t CANMessage::getReceivingChannel()
{
	if (!_receivingController) {
		return CAN::num_can_channels; // this basically serves as "None" now.
	}
	return _receivingController->getChannel();
}

void CANMessage::setReceivingController(CANController *_receivingController)
{
    this->_receivingController = _receivingController;
}

void CANMessage::assign(const CANMessage *msg)
{
	_flags = msg->_flags;
	_receivingController = msg->_receivingController;
	id = msg->id;
	dlc = msg->dlc;
	memcpy(data, msg->data, sizeof(data));
}

void CANMessage::returnMessageToPool()
{
	_receivingController->returnMessageToPool(this);
}

uint64_t CANMessage::extractSignal(uint8_t startBit, uint8_t bitCount)
{
	if ( (startBit+bitCount) > 64) { return 0; }

	uint64_t result = (data[0])
					| ((uint64_t)data[1]<<8)
					| ((uint64_t)data[2]<<16)
					| ((uint64_t)data[3]<<24)
			        | ((uint64_t)data[4]<<32)
			        | ((uint64_t)data[5]<<40)
			        | ((uint64_t)data[6]<<48)
			        | ((uint64_t)data[7]<<56);
	result >>= startBit;
	result  &= (0xFFFFFFFFFFFFFFFF >> (64-bitCount));

	return result;
}


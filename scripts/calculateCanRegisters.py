#!/usr/bin/env python3

'''
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Stefan Rupp <struppi@struppi.name> wrote this file. As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day,
 * and you think this stuff is worth it, you can buy me a beer in return.
 * (c) 2016 Stefan Rupp
'''

from optparse import OptionParser


def getSamplingPoint(bs1, bs2):
	sp = (1+bs1)/(bs1+bs2+1.0)
	return sp


def getDivisor(baudrate, clock, bs1, bs2):
	brp = clock/(baudrate*(1.0+bs1+bs2))
	if brp == int(brp): # Check if divisor is integer 
		return brp
	return None

def main():
	parser = OptionParser()
	parser.add_option("-b", "--baudrate", dest="baudrate", type="int", default="500000", help="baudrate for CAN (e.g. 500000)", metavar="BAUDRATE")
	parser.add_option("-c", "--pclk1", dest="clock", type="int", default="45000000", help="Clock of CAN subsystem", metavar="PCLK1")
	parser.add_option("-H", "--sphigh", dest="sp_high", help="Sampling Point high value", metavar="SPHIGH")
	parser.add_option("-L", "--splow", dest="sp_low", help="Sampling Point low value", metavar="SPLOW")
	parser.add_option("-X", "--calcDefaults", dest="calc_defaults", action="store_true", help="Calculate best values for default baudrates")
	parser.add_option("-D", "--calcDivisor", dest="calc_divisor", action="store_true", help="Calculate divisor for given values of BS1 and BS2")
	parser.add_option("-s", "--bs1", dest="bs1", type="int", help="Value for BS1, only used with -D")
	parser.add_option("-S", "--bs2", dest="bs2", type="int", help="Value for BS2, only used with -D")
	(options, args) = parser.parse_args()

	if options.sp_low:
		spLow = int(options.sp_low) / 100
	else:
		spLow = 0.65

	if options.sp_high:
		spHigh = int(options.sp_high) / 100
	else:
		spHigh = 0.80

	## First mode, command line arguments: "-D" in conjunction with "-s" and "-S"
	## This mode calculates the appropriate divider for given BS1 and BS2 values
	if options.calc_divisor: 
		can_baudrates = [100000, 125000, 250000, 500000, 1000000]
		print("clock = ", options.clock)
		for br in can_baudrates:
			d = getDivisor(br, options.clock, options.bs1, options.bs2)
			sp = getSamplingPoint(options.bs1, options.bs2)
			if d:
				print("baudrate =",br)
				print("good: **sp=%f** ==> bs1=%d, bs2=%d, div=%d"%(sp, options.bs1, options.bs2, d))
	## Second mode, command line argument "-X"
	## This mode calculates appropriate setting for some common CAN baudrates
	elif options.calc_defaults:
		can_baudrates = [100000, 125000, 250000, 500000, 1000000]
		sp_ideal=0.75
		print("clock=", options.clock)
		for br in can_baudrates:
			print ("baudrate: ",br)
			(sp_current, bs1_current, bs2_current, d_current) = (0, 0, 0, 0)
			for bs1 in range(1,17):
				for bs2 in range(1,9):
					sp = getSamplingPoint(bs1, bs2)
					d = getDivisor(br, options.clock, bs1, bs2)
					if d and spLow <= sp <= spHigh and abs(sp_ideal-sp_current) > abs(sp_ideal-sp):
						sp_current = sp
						bs1_current = bs1
						bs2_current = bs2
						d_current = d
			if (bs1_current != 0 and bs2_current != 0 and sp_current != 0):
				print("good: **sp=%f** ==> bs1=%d, bs2=%d, div=%d"%(sp_current, bs1_current, bs2_current, d_current))
			else:
				print("FAILED for BAUDRATE==", br)
	## Third mode
	## Try to find all valid setting for a given baudrate and CAN subsytem clock rate
	else:
		print ("c=%d and b=%d"%(options.clock,options.baudrate))
		print ("Sample Point: min==%f%% and max==%f%%"%(spLow*100, spHigh*100))

		for bs1 in range(1,17):
			for bs2 in range(1,9):
					#print ("bs1=%d and bs2=%d"%(bs1,bs2))
					sp = getSamplingPoint(bs1, bs2)
					if spLow <= sp <= spHigh:
							d = getDivisor(options.baudrate, options.clock, bs1, bs2)
							if d:
								print("good: **sp=%f** ==> bs1=%d, bs2=%d, div=%d"%(sp, bs1, bs2, d))

	
	
if __name__ == "__main__":
	main()

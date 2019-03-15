#!/usr/bin/python
# -*- coding: utf-8 -*-

#import time

import win32gui
import ctypes
#from ctypes import *


##########################NOTES
#open text.txt with Notepad manualy. Only one instance of Notepad.
##########################

def LoadTablemap(dll, name):
	'''
	loading table map
	'''
	res = dll.OpenTablemap(name)
	print ('res:', res ),
	return res

def ReadRegionWithOffset(dll, hWnd, name, offset=0):
#;Function to read a region using a window ($hWnd) and name of region
	t = (ctypes.c_char_p*1)(b'')
	try:
		res = dll.ReadRegion(hWnd, name, t, offset)
	except Exception, er:
		print 'ERROR:', er
		return 'error'

	#print res
	return t[0]

def GetCoordRegion(dll, name):
#;Function to get Coord from a region ($name)
	posleft = (ctypes.c_int*1)()
	postop = (ctypes.c_int*1)()
	posright = (ctypes.c_int*1)()
	posbottom = (ctypes.c_int*1)()

	try:
		res = dll.GetRegionPos(name, posleft, postop, posright, posbottom)
	except Exception, er:
		print 'ERROR:', er
		return 'error'

	return [posleft[0], postop[0], posright[0], posbottom[0]]


if __name__=='__main__':

#;Specify OpenScrapeDLL (don't change)
	dllName = "OpenScrapeDLL.dll"

#;Specify your Table Map
	tableMap = "OpenScrapeExampleTM.tm"

#;Specify Tittle Window (for this example we will use notepad)
	classWindow = "Notepad"

#;We need hwnd from the window
#$hWnd1 = WinGetHandle($tittleWindow)
	hWnd1 = win32gui.FindWindow(classWindow, None)

	print('handle: %s' % hWnd1)


#;We activate the window
	print ('activating'),
	win32gui.SetForegroundWindow(hWnd1)
	print ('+')


#;Opening Dll
	print ('Opening Dll'),
#Local $dll = DllOpen($dllName)
	#dll = ctypes.WinDLL(dllName)
	dll = ctypes.CDLL(dllName)
	#dll = cdll.LoadLibrary(dllName)
	#print dll
	print ('+')

#;Loading Table Map
	print ('Loading Table Map'),
	LoadTablemap(dll, tableMap)
	#dll.OpenTablemap(tableMap)
	#print 'res:', res
	print ('+')


#;==========================================================================================
#;Define your Table Map Region
	regions = [
		"test",
		"test2",
		"isTrue",
		"normal",
	]
	i = 0
	for region in regions:
		i+=1
		print '\n'*2,

		print ("read a region %s/%s '%s'" % (i, len(regions), region)),
		scraped = ReadRegionWithOffset(dll, hWnd1, region)
		print "scraped: '%s'" % scraped

		coords = GetCoordRegion(dll, region)
		print ("	coords for %s: %s" % (region, coords))

#;==========================================================================================

#;Don't forge to close Dll
#DllClose($dll)


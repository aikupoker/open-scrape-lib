#cs ----------------------------------------------------------------------------

	AutoIt Version: 3.3.4.0
	Author:         Aiku

	Script Function:
	Table Map Dll usage

#ce ----------------------------------------------------------------------------


;Specify OpenScrapeDLL (don't change)
Global $dllName = "OpenScrapeDLL.dll"

;Specify your Table Map
Global $tableMap = "OpenScrapeExampleTM.tm"

;Specify Tittle Window (for this example we will use notepad)
Global $tittleWindow = "test.txt"


If Not WinExists($tittleWindow) Then
	;Open test.txt
	MsgBox(4096, "Hey!", "Open " & $tittleWindow & " to scrape some regions! ")
EndIf


;We need hwnd from the window
Local $hWnd1 = WinGetHandle($tittleWindow)
;We activate the window
WinActivate($hWnd1)
If @error Then
	MsgBox(4096, "Error", "Could not find the correct window")
	Exit
EndIf



;Opening Dll
Local $dll = DllOpen($dllName)

;Loading Table Map
LoadTablemap($tableMap)


;==========================================================================================
;Define your Table Map Region
Local $tmRegion0 = "test"

;Let's read a region! (Text region)
Local $res = ReadRegionWithOffset($hWnd1, $tmRegion0, 0)

;Results
ConsoleWrite("TableMap Usage Example: (Region: " & $tmRegion0 & "). Text scraped: " & $res & @CRLF)
;==========================================================================================


;==========================================================================================
;Example 2
;Define your Table Map Region
Local $tmRegion1 = "test2"

;Let's read another region! (Text region)
Local $res = ReadRegionWithOffset($hWnd1, $tmRegion1, 0)

;Results
ConsoleWrite("TableMap Usage Example: (Region: " & $tmRegion1 & "). Text scraped: " & $res & @CRLF)
;==========================================================================================



;==========================================================================================
;Example 3
;Define your Table Map Region
Local $tmRegion2 = "isTrue"

;Let's read another region! (Color region)
Local $res = ReadRegionWithOffset($hWnd1, $tmRegion2, 0)

;Results
ConsoleWrite("TableMap Usage Example: (Region: " & $tmRegion2 & "). Text scraped: " & $res & @CRLF)
;==========================================================================================




;==========================================================================================
;Example 4
;Define your Table Map Region
Local $tmRegion3 = "normal"

;Lets Get coord from the region
Local $coord = GetCoordRegion($tmRegion3)

;Results (see rectangle image)
ConsoleWrite("TableMap Usage Example: " & @CRLF)
ConsoleWrite(@TAB & "-Region name: " & $coord[1] & @CRLF)
ConsoleWrite(@TAB & "-Rectangle 1: " & $coord[2] & @CRLF)
ConsoleWrite(@TAB & "-Rectangle 2: " & $coord[3] & @CRLF)
ConsoleWrite(@TAB & "-Rectangle 3: " & $coord[4] & @CRLF)
ConsoleWrite(@TAB & "-Rectangle 4: " & $coord[5] & @CRLF)

;==========================================================================================

;Don't forge to close Dll
DllClose($dll)



;------- Functions -------

;Function to load Table Map in Dll
Func LoadTablemap($name)

	Local $res = DllCall($dll, "int:cdecl", "OpenTablemap", "str", $name)

	If (@error <> 0) Then
		ConsoleWrite("ERROR in dllcall(OpenTablemap) " & @error & @CRLF)
		Exit
	EndIf

	If ($res[0] = 0) Then
		ConsoleWrite("ERROR in OpenTablemap with map " & $tableMap & @CRLF)
		Exit
	EndIf
EndFunc   ;==>LoadTablemap

;Function to read a region using a window ($hWnd) and name of region
Func ReadRegion($hWnd, $name)
	Return ReadRegionWithOffset($hWnd, $name, 0)
EndFunc   ;==>ReadRegion

;Function to read a region using a window ($hWnd) and name of region
Func ReadRegionWithOffset($hWnd, $name, $offset)
	Local $res = DllCall($dll, "int:cdecl", "ReadRegion", "hwnd", $hWnd, "str", $name, "str*", "", "int", $offset)

	If (@error <> 0) Then
		ConsoleWrite("ERROR in dllcall(ReadRegion) " & @error & @CRLF)
		Exit
	EndIf

	Return $res[3]

EndFunc   ;==>ReadRegionWithOffset

;Function to get Coord from a region ($name)
Func GetCoordRegion($name)
	Local $posl
	Local $posr
	Local $post
	Local $posb

	Local $res = DllCall($dll, "none:cdecl", "GetRegionPos", "str", $name, "int*", $posl, "int*", $post, "int*", $posr, "int*", $posb)

	if (@error <> 0) Then
		ConsoleWrite("ERROR in dllcall(ReadRegion) " & @error & @CRLF)
		Exit
	EndIf

	Return $res

EndFunc   ;==>GetCoordRegion



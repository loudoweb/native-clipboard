package haxe.extension;

import ammer.Library;
import ammer.ffi.*;
import haxe.io.Bytes;
import haxe.extension.EClipboard;

class Clipboard extends Library<"clipboard"> {
	public static function count_formats():Int;
	public static function list_available_format():String;
	public static function get_text():String;
	public static function get_image(loaded:SizeOfReturn):haxe.io.Bytes;
	public static function get_data(type:String):String;
	public static function get_bytes(type:String, loaded:SizeOfReturn):haxe.io.Bytes;
}
package haxe.extension;

import ammer.Library;
import ammer.ffi.*;
import haxe.io.Bytes;

class Clipboard extends Library<"clipboard"> {
	/**
	 * Count all formats available.
	 * @return Int
	 */
	public static function count_formats():Int;
	/**
	 * Get all format names
	 * @return String format separated by commas
	 */
	public static function list_available_format():String;
	/**
	 * Get basic text
	 * @return String
	 */
	public static function get_text():String;
	/**
	 * Get an image (PNG first, then fallback to CF_BITMAP and CF_DIB)
	 * @return haxe.io.Bytes
	 */
	public static function get_image(loaded:SizeOfReturn):haxe.io.Bytes;
	/**
	 * Get data as a string.
	 * @param type You can use EClipboard to have some common formats.
	 * @return String
	 */
	public static function get_data(type:String):String;
	/**
	 * Get data as bytes.
	 * @param type You can use EClipboard to have some common formats. e.g: get_bytes("PNG")
	 * @return haxe.io.Bytes
	 */
	public static function get_bytes(type:String, loaded:SizeOfReturn):haxe.io.Bytes;

	public static function clear():Int;

	public static function set_text(str:String):Int;

	public static function set_data(type:String, str:String):Int;

}
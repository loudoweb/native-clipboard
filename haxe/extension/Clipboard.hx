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
	 * @param type You can use EClipboard.hx to have some common formats. e.g: get_bytes("PNG")
	 * @return haxe.io.Bytes
	 */
	public static function get_bytes(type:String, loaded:SizeOfReturn):haxe.io.Bytes;

	/**
	 * 
	 * You should clear the clipboard once before writing anything
	 * @return Bool
	 */
	public static function clear():Bool;

	/**
	 * Simple text
	 * @param str 
	 * @return Bool
	 */
	public static function set_text(str:String):Bool;

	/**
	 * Write other kind of strings in the clipboard like html, svg, etc.
	 * @param type You can use EClipboard to have some common formats.
	 * @param str Some formats may need additional treatment that you can find in ClipboardUtils.hx
	 * @return Bool success
	 */
	public static function set_data(type:String, str:String):Bool;

	/**
	 * Write PNG
	 * @param data PNG only
	 * @return Bool success
	 * 
	 */
	public static function set_image(data:Bytes, dataLen:SizeOf<"data">):Bool;

	/**
	 * Write bytes
	 * @param type You can use EClipboard to have some common formats.
	 * @param data 
	 * @return Bool succes
	 */
	public static function set_bytes(type:String, data:Bytes, dataLen:SizeOf<"data">):Bool;

}
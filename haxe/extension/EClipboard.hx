package haxe.extension;

enum abstract EClipboard(String) to String{
	var TEXT = "CF_TEXT";
	var UNICODE = "CF_UNICODETEXT";
	var IMAGE = "PNG"; 
	var HTML = "HTML Format";
	var SVG = "image/x-inkscape-svg";
	var PDF = "PORTABLE DOCUMENT FORMAT";
	var FILES = "List of Files";
  
	inline function new(i:String) {
		this = i;
	}
	inline public static function CUSTOM(str:String):EClipboard
	{
		return new EClipboard(str);
	}
}
package haxe.extension;

enum abstract EClipboard(String) to String{
	var TYPE_IMAGE = "CF_DIB"; 
	var TYPE_TEXT = "CF_TEXT";
	var TYPE_HTML = "HTML Format";
	var TYPE_SVG = "image/x-inkscape-svg";
	var TYPE_AI = "PORTABLE DOCUMENT FORMAT";
	var TYPE_FILES = "List of Files";
  
	inline function new(i:String) {
		this = i;
	}
	inline public static function CUSTOM(str:String):EClipboard
	{
		return new EClipboard(str);
	}
}
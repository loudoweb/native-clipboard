package haxe.extension;

class ClipboardUtils {
	/**
	 * Build a html clibboard
     * @param input string
	 * @return String in the correct clipboard format
	 */
	public static function formatHTML(input:String):String
    {
        var len = input.length;

        var output = "Version:0.9\n";
        output += "StartHTML:0000000105\n";
        output += "EndHTML:" + formatIndex(105, len) + "\n";
        output += "StartFragment:0000000141\n";
        output += "EndFragment:" + formatIndex(141, len) + "\n";
        output += "<html>\n";
        output += "<body>\n";
        output += "<!--StartFragment-->" + input + "<!--EndFragment-->\n";
        output += "</body>\n";
        output += "</html>\n";
        return output;
    }

    public static function getString(str:String, format:EClipboard = HTML):String
    {
        if(str != "")
        {
            switch(format)
            {
                case HTML:
                    var begin = str.indexOf("<!--StartFragment-->");
                    var end = str.indexOf("<!--EndFragment-->");
                    return str.substring(begin + 20, end);
                case SVG:
                    var end = str.indexOf("</svg>");
                    return str.substring(0, end + 6);
                default:
                    return str;
            }
        }
        return str;
    }

    static function formatIndex(start:Int, len:Int):String
    {
        var str:String = "";
        var fullLen = start + len;
        var fStr = Std.string(fullLen);
        for(i in fStr.length...10)
        {
            str += "0";
        }

        str += fStr;
        return str;
    }

}
import haxe.extension.Clipboard;
import haxe.extension.EClipboard;

class Sample {
  public static function main():Void {
	var count = Clipboard.count_formats();
    trace('count ${count}');
	trace("formats ", ${Clipboard.list_available_format().split(",")});
    trace('---');
    trace('text: ${Clipboard.get_text()}');
    trace('image: ${Clipboard.get_image()}');
    trace('html: ${Clipboard.get_data(EClipboard.TYPE_HTML)}');
    trace('svg: ${Clipboard.get_data("image/x-inkscape-svg")}');
    trace('pdf: ${Clipboard.get_bytes("Portable Document Format")}');
	trace('image2: ${Clipboard.get_bytes("PNG")}');
	trace('list: ${Clipboard.get_bytes("DataObject")}');
  }
}

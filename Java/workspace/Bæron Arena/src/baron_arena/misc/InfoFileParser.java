package baron_arena.misc;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Hashtable;

public class InfoFileParser {
	private Hashtable<String, String> dataDict;
	
	public InfoFileParser(InputStream stream) throws IOException {
		dataDict = getDictFromStream(stream);
	}
	
	public InfoFileParser(String path) throws FileNotFoundException, IOException {
		this(InfoFileParser.class.getResourceAsStream(path));
	}
	
	public String get(String key) {
		return dataDict.get(key);
	}
	
	@SuppressWarnings("unchecked") // Because dataDict.clone() returns a Hashtable, not knowing the generics are
	public Hashtable<String, String> asDict() {
		return (Hashtable<String, String>) dataDict.clone();
	}
	
	public static Hashtable<String, String> getDictFromStream(InputStream stream) throws IOException {
		BufferedReader infoReader = new BufferedReader(new InputStreamReader(stream));
		Hashtable<String, String> dataDict = new Hashtable<String, String>();
		String line;
		
		while ((line = infoReader.readLine()) != null) {
			String[] lineComponents = line.split(":");
			
			if (lineComponents.length != 2) {
				continue;
			}
			
			dataDict.put(lineComponents[0].trim(), lineComponents[1].trim());
		}
		
		return dataDict;
	}
	
	public static Hashtable<String, String> getDictFromStream(String path) throws IOException {
		return getDictFromStream(new FileInputStream(path));
	}
}

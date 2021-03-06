//import org.apache.commons.lang.StringEscapeUtils;

public class UnescapeUnicode {
    public static void main(String[] args) {
        String in = "Hall\\u00F6, World!";
        System.out.println(in);
        String out = unescapeUnicode2(in);
        System.out.println(out);
    }

    public static String unescapeUnicode(String s) {
        StringBuilder sb = new StringBuilder();

        int oldIndex = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.substring(i, i + 2) == "\\u") {
                sb.append(s.substring(oldIndex, i));
                int codePoint = Integer.parseInt(s.substring(i + 2, i + 6), 16);
                sb.append(Character.toChars(codePoint));
                i += 5;
                oldIndex = i;
            }
        }

        return sb.toString();
    }

public static String unescapeUnicode2(String s) {
    StringBuilder sb = new StringBuilder();

    int oldIndex = 0;

    for (int i = 0; i + 2 < s.length(); i++) {
        if (s.substring(i, i + 2).equals("\\u")) {
            sb.append(s.substring(oldIndex, i));
            int codePoint = Integer.parseInt(s.substring(i + 2, i + 6), 16);
            sb.append(Character.toChars(codePoint));
            i += 5;
            oldIndex = i;
        }
    }

    sb.append(s.substring(oldIndex + 1, s.length()));

    return sb.toString();
}
}

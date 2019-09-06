import java.util.ArrayList;
import java.lang.StringBuilder;
import java.util.Collections;
import java.util.HashMap;
import java.lang.Integer;


class Solution {
  public String[] solution(String[] files) {
    String[] answer = {};
    
    ArrayList<String[]> temp = new ArrayList<>();    
    HashMap<String[], String> originMap = new HashMap<>();

    for(String file: files) {
      StringBuilder sb = new StringBuilder();
      
      String header = "";
      String number = ""; 
      String tail = "";
      for(int i = 0; i < file.length(); i++) {
        char c = file.charAt(i);
        if(Character.isDigit(c) && header.equals("")) {
          header = sb.toString();
          sb = new StringBuilder();
        } else if(header.equals("") == false && number.equals("") && Character.isDigit(c) == false) {
          number = sb.toString();
          tail = file.substring(i, file.length());
          break;
        }
        sb.append(c);

        if(i == file.length() - 1 && number.equals("")) {
          number = sb.toString();
        }
      }
      

      String[] strArray = new String[] {
        header.toLowerCase(), number, tail
      };
      temp.add(strArray);

      originMap.put(strArray, file);
    }

    Collections.sort(temp, (arr1, arr2) -> {
      if(arr1[0].equals(arr2[0])) {
        return Integer.parseInt(arr1[1]) - Integer.parseInt(arr2[1]);
      } else {
        return arr1[0].compareTo(arr2[0]);
      }
    });

    answer = temp.stream()
      .map(arr -> originMap.get(arr)) 
      .toArray(String[]::new);


    return answer;
  }
}
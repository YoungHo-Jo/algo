import java.util.Arrays;

class Solution {
  public boolean solution(String[] phone_book) {
    boolean answer = true;

    Arrays.sort(phone_book);

    for(int i = 0; i < phone_book.length; i++) {
      String phone = phone_book[i];

      int found = Arrays.binarySearch(phone_book, phone, (p, target) -> {
        if(p.length() < target.length()) {
          return p.compareTo(target.substring(0, p.length()));
        }

        return p.substring(0, target.length()).compareTo(target);
      });

      if(found != -1 && found != i) {
        answer = false;
        break;
      }
    }

    return answer;
  }
}
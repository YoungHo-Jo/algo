import java.util.Iterator;
import java.util.LinkedList;



class Solution {
  public int solution(int cacheSize, String[] cities) {
    int answer = 0;

    LinkedList<String> cache = new LinkedList<>();
    for(String citi: cities) {
      citi = citi.toLowerCase();

      boolean hit = false;
      Iterator<String> it = cache.iterator();
      while(it.hasNext()) {
        String here = it.next();
        if(here.equals(citi)) {
          // hit
          it.remove();
          cache.add(0, here); 
          answer += 1;
          hit = true;
          break;
        }
      }

      if(hit == false) {
        // mise
        if(cache.size() >= cacheSize && cache.isEmpty() == false) {
          cache.removeLast();
        }
        if(cache.size() < cacheSize) {
          cache.add(0, citi);
        }
        answer += 5;
      }
    }

    return answer;
  }
}
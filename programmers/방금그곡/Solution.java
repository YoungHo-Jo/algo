import java.util.ArrayList;
import java.util.Arrays;

class Solution {

  public String solution(String m, String[] musicinfos) {
    String answer = "(None)";
    int topPlaySecs = 0;
    for(String info: musicinfos) {
      String[] tokens = info.split(",");
      int[] startTime = Arrays.stream(tokens[0].split(":"))
        .mapToInt(s -> Integer.parseInt(s))
        .toArray();
      int[] endTime = Arrays.stream(tokens[1].split(":"))
        .mapToInt(s -> Integer.parseInt(s))
        .toArray();
      int playSecs = (endTime[0] - startTime[0])*60;
      playSecs += endTime[1];
      playSecs -= startTime[1];
      
      String music = tokens[3];
      int musicIndex = 0; 
      int melodyIndex = 0;
      int secs = playSecs;
      while(secs >= 0) {
        if(music.charAt(musicIndex) == m.charAt(melodyIndex)) {
          melodyIndex++;
        } else {
          melodyIndex = 0; 
        }
        
        int nextIndex = (musicIndex + 1)%music.length();
        if(music.charAt(nextIndex) != '#') {
          secs--;
        }
        musicIndex = nextIndex;

        if(melodyIndex == m.length()) {
          // end with '#' or 'C|F...'
          if(music.charAt(musicIndex) == '#') {
            // if actual sound is 'C#' in music but matched only 'C' in melody
            melodyIndex = 0;
          } else {
            break;
          }
        }
      }

      if(melodyIndex == m.length()) {
        if(answer.equals("(None)") || topPlaySecs < playSecs) {
          answer = tokens[2]; 
          topPlaySecs = playSecs;
        } 
      }
    } 

    return answer;
  }
}

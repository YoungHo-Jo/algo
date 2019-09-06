import java.util.Arrays;

class Solution {

  public String solution(String m, String[] musicinfos) {
    String answer = "";

    m = this.change(m);
    int topPlaySecs = 0;
    for(String info: musicinfos) {
      String[] tokens = info.split(",");
      int[] startTime = Arrays.stream(tokens[0].split(":"))
        .mapToInt(s -> Integer.parseInt(s))
        .toArray();
      int[] endTimes = Arrays.stream(tokens[1].split(":"))
        .mapToInt(s -> Integer.parseInt(s))
        .toArray();
      int playSecs = Math.abs(endTimes[0]*60 + endTimes[1] - (startTime[0]*60 + startTime[1]));

      String music = tokens[3];
      music = this.change(music);

      /* Method 1 */
      int musicIndex = 0;
      int melodyIndex = 0;
      int secs = playSecs;
      while(secs > 0) {
        if(music.charAt(musicIndex) == m.charAt(melodyIndex)) {
          melodyIndex++;
        } else {
          melodyIndex = 0;
        }

        if(melodyIndex == m.length()) {
          break;
        }

        musicIndex = (musicIndex + 1)%music.length(); 
        secs--;
      }

      if(melodyIndex == m.length()) {
        if(topPlaySecs == 0 || topPlaySecs < playSecs) {
          answer = tokens[2];
          topPlaySecs = playSecs;
        }  
      }
  
      /* Method 2 */
      // StringBuilder sb = new StringBuilder();
      // int j = 0;
      // for(int i = 0; i < playSecs; i++) {
      //   j = i%music.length();
      //   sb.append(music.charAt(j)); 
      // }
      // 
      // if(sb.toString().contains(m)) {
      //   if(topPlaySecs == 0 || topPlaySecs < playSecs) {
      //     answer = tokens[2];
      //     topPlaySecs = playSecs;
      //   }
      // }
    }

    return answer.equals("") ? "(None)" : answer;
  }

  String change(String music) {
    music = music.replace("C#", "c")
      .replace("D#", "d")
      .replace("F#", "f")
      .replace("G#", "g")
      .replace("A#", "a");
    return music;
  }
  
}
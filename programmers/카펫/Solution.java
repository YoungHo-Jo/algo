
class Solution {
  public int[] solution(int brown, int red) {
    int[] answer = new int[2];

    int size = brown + red;
    int width = size;
    int height = 1;

    while(height <= width) {
      // System.out.println(String.format("width: %d height: %d ", width, height));

      // check brown and red
      if(width * height == size) {
        if(height >= 3  && red != 0) {
          int brownCnt = 2 * width + 2 * height - 4;
          // System.out.printf("brownCnt: %d", brownCnt);
          if(brownCnt == brown) {
            break;
          }
        } else if(height == 1 && red == 0) {
          break;
        } 
      } 
      
      // update height and width
      height++;
      width = size / height;
    }

    answer[0] = width;
    answer[1] = height;


    return answer;
  }
}
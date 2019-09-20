import java.util.Comparator;
import java.util.PriorityQueue;

class Solution {
  public int[] solution(String[] operations) {
    int[] answer = new int[2];

    PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());
    PriorityQueue<Integer> minHeap = new PriorityQueue<>();


    for(String op: operations) {
      char cmd = op.charAt(0);
      String numStr = op.split(" ")[1];
      Integer num = Integer.parseInt(numStr);

      if(cmd == 'I') {
        minHeap.offer(num);
        maxHeap.offer(num);
      } else {
        if(num == 1) {
          Integer max = maxHeap.poll();
          minHeap.remove(max);
        } else {
          Integer min = minHeap.poll();
          maxHeap.remove(min);
        }
      }
    }

    if(maxHeap.isEmpty()) {
      answer[0] = 0;
      answer[1] = 0;
    } else {
      answer[0] = maxHeap.peek();
      answer[1] = minHeap.peek();
    }
    

    return answer;
  }
}
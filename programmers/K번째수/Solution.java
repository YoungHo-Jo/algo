import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

class Solution {
  public int[] solution(int[] array, int[][] commands) {
    int[] answer = {};

    List<Integer> list = Arrays
      .stream(array)
      .boxed()
      .collect(Collectors.toList());

    ArrayList<Integer> result = new ArrayList<>(commands.length);
    for(int i = 0; i < commands.length; i++) {
      int[] comd = commands[i];
      ArrayList<Integer> sublist = new ArrayList<>(
        list.subList(comd[0] - 1, comd[1])
      );
      Collections.sort(sublist);
      result.add(sublist.get(comd[2] - 1));
    }

    return result
      .stream()
      .mapToInt(i -> Integer.valueOf(i))
      .toArray();
  }
}
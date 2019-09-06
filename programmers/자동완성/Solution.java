import java.util.HashMap;

class Solution {
  class Node {
    char c;
    int cnt;
    HashMap<Character, Node> children;
    
    Node(char _c) {
      this.c = _c;
      this.cnt = 1;
      children = new HashMap<>();
    }
  }

  class Tree {
    Node root = null;

    void add(String word) {
      if(root == null) {
        root = new Node('0');
      }
      
      this.add(root, word);
    } 

    void addRcurs(Node here, String word) {
      if(word.length() == 0) return;
      char c = word.charAt(0);

      if(here.children.containsKey(c)) {
        Node child = here.children.get(c);
        child.cnt++;
        this.add(child, word.substring(1, word.length()));
      } else {
        Node newChild = new Node(c);
        here.children.put(c, newChild);
        this.add(newChild, word.substring(1, word.length()));
      }
    }
    
    void add(Node here, String word) {
      if(word.length() == 0) return;
      int wordIndex = 0;

      while(wordIndex < word.length()) {
        char c = word.charAt(wordIndex);

        if(here.children.containsKey(c)) {
          here = here.children.get(c);
          here.cnt++;
        } else {
          Node newChild = new Node(c);
          here.children.put(c, newChild);
          here = newChild;
        }

        wordIndex++;
      }
    }

    int count(String word) {
      if(word.length() == 0) return 0;
      return count(root, word, 0);
    }

    int countRecurs(Node here, String word, int cnt) {
      if(word.length() == 0) return 0;
      char c = word.charAt(0);
      Node child = here.children.get(c);

      if(child.cnt == 1 || word.length() == 1) {
        return cnt + 1;
      } else {
        return count(child, word.substring(1, word.length()), cnt + 1);
      }
    }

    int count(Node here, String word, int cnt) {
      if(word.length() == 0) return 0;
      int wordIndex = 0;

      while(wordIndex < word.length()) {
        char c = word.charAt(wordIndex);
        Node child = here.children.get(c);
        if(child.cnt == 1 || wordIndex == word.length() - 1) {
          cnt++;
          break;
        } else {
          here = child;
          cnt++; 
          wordIndex++;
        }       
      }

      return cnt;
    }
  }

  public int solution(String[] words) {
    int answer = 0;

    Tree tree = new Tree();
    for(String s: words) {
      tree.add(s);
    }

    for(String s: words) {
      answer += tree.count(s); 
    }

    return answer;
  }
}
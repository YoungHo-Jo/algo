import java.util.ArrayList;

class Solution {
  class Point {
    int x;
    int y;
    Point(int _x, int _y) {
      this.x = _x;
      this.y = _y;
    }

    Point(Point point) {
      this.x = point.x;
      this.y = point.y;
    }

    @Override
    public boolean equals(Object obj) {
      Point point = (Point) obj;
      return point.x == this.x && point.y == this.y;
    }

    @Override
    public String toString() {
      return String.format("(%d, %d)", x, y);
    }
  }

  class Line {
    Point p1;
    Point p2;

    Line(Point p1, Point p2) {
      this.p1 = p1;
      this.p2 = p2;
    }

    @Override
    public boolean equals(Object obj) {
      Line line = (Line) obj;
      if(line.p1.equals(this.p1)) {
        return line.p2.equals(this.p2);
      }

      if(line.p2.equals(this.p1)) {
        return line.p1.equals(this.p2);
      }

      return false;
    }

  }

  class GameChar {
    private static final int SIZE = 5;
    Point current;
    
    GameChar(Point _current) {
      this.current = _current; 
    }

 
    void up() {
      if(current.y < SIZE) {
        current.y++;
      }
    }

    void down() {
      if(current.y > -SIZE) {
        current.y--; 
      }
    }

    void right() {
      if(current.x < SIZE) {
        current.x++;
      }
    }

    void left() { 
      if(current.x > -SIZE) {
        current.x--;
      }
    }

  }
  public int solution(String dirs) {
    int answer = 0;

    GameChar gameChar = new GameChar(new Point(0, 0));
    ArrayList<Line> history = new ArrayList<>();

    for(char c: dirs.toCharArray()) {
      Point before = new Point(gameChar.current);

      switch(c) {
        case 'U':
          gameChar.up(); 
          break;
        case 'D':
          gameChar.down();
          break;
        case 'R':
          gameChar.right();
          break;
        case 'L':
          gameChar.left();
          break;
        default:
          throw new RuntimeException();
      } 
      Point after = new Point(gameChar.current);


      if(before.equals(after)) {
      }  else if(history.contains(new Line(before, after))) {
      } else {
        history.add(new Line(before, after));
        answer++;
      }
    }

    return answer;
  }
}
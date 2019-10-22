import java.util.ArrayList;
import java.util.List;

class BST {

  private Node root;
  private int size;
  
  public BST(Node root) {
    this.root = root;
    this.size = 1;
  }

  public BST() {
    this.root = null;
    this.size = 0;
  }

  public int size() {
    return this.size;
  }

  public Node getRoot() {
    return this.root;
  }
  
  private void sizeUp() {
    this.size++;
  }

  private void sizeDown() {
    this.size--;
  }

  public void insert(Node node) {
    if(node == null) {
      throw new RuntimeException("null node is not accepted");
    }

    this.root = insertNode(this.root, node);
  }

  private Node insertNode(Node here, Node target) {
    if(here == null) {
      this.sizeUp();
      return target;
    }


    if(target.getValue() < here.getValue()) {
      here.setLeft(this.insertNode(here.getLeft(), target));
    } else if(here.getValue() < target.getValue()) {
      here.setRight(this.insertNode(here.getRight(), target));
    } 

    return here;
  }

  public void clear() {
    this.clear(this.root);     
  }

  private void clear(Node node) {
    if(node != null) {
      this.clear(node.getLeft());
      this.clear(node.getRight());
      node = null;
    }
  }

  public void convertToBalanced() {
    List<Node> inOrders = this.inOrder();
    this.clear();
    this.root = buildBalanced(inOrders, 0, inOrders.size() - 1);
  }

  private Node buildBalanced(List<Node> nodes, int start, int end) {
    if(start > end) {
      return null;
    }

    int mid = (start + end) / 2;
    Node node = nodes.get(mid);
    
    node.setLeft(buildBalanced(nodes, start, mid - 1));
    node.setRight(buildBalanced(nodes, mid + 1, end));

    return node;
  }

  public List<Node> inOrder() {
    ArrayList<Node> order = new ArrayList<>(); 
    this.inOrder(this.root, order);    
    return order;
  }

  private void inOrder(Node node, List<Node> order) {
    if(node == null) {
      return;
    }

    if(node.getLeft() != null) {
      inOrder(node.getLeft(), order);
    } 

    order.add(node);

    if(node.getRight() != null) {
      inOrder(node.getRight(), order);
    }
  }

  public Node find(Node node) {
    return this.find(this.root, node, 0) == false ? null : node;
  }

  private boolean find(Node here, Node target, int depth) {
    if(here != null) {
      if(here.getValue() == target.getValue()) {
        System.out.println("found depth: " + depth);
        return true;
      } 

      if(target.getValue() < here.getValue()) {
        return find(here.getLeft(), target, depth + 1);
      } 

      if(here.getValue() < target.getValue()) {
        return find(here.getRight(), target, depth + 1);
      }
    }

    return false;
  }
  

  public static void main(String[] args) {

    BST bst = new BST();
    int[] arr = {
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
    };

    for(int i = 0; i < arr.length; i++) {
      Node node = new Node(arr[i]);
      bst.insert(node); 
    } 

    System.out.println("Search something...");
    for(int i = 5; i < 20; i++) {
      Node node = new Node(i);
      if(bst.find(node) != null) {
        System.out.println(i + " found");
      } else {
        System.out.println(i + " not found");
      }
    }

    System.out.println("Before balanced: ");
    System.out.println(bst.getRoot().toString());
  
    bst.convertToBalanced();

    System.out.println("Search something...");
    for(int i = 5; i < 15; i++) {
      Node node = new Node(i);
      if(bst.find(node) != null) {
        System.out.println(i + " found");
      } else {
        System.out.println(i + " not found");
      }
    }

    System.out.println("After balanced: ");
    System.out.println(bst.getRoot().toString());
  }

  static class Node {
    private int value;
    private Node left, right;
    
    Node(int value) {
      this.value = value;
    }

    @Override
    public String toString() {
      return String.format("Node(%d, %s, %s)", this.value, this.left, this.right);
    }
    
    Node setLeft(Node node) {
      this.left = node;
      return this.left;
    }
    
    Node setRight(Node node) {
      this.right = node;
      return this.right;
    }

    Node getLeft() {
      return this.left;
    }

    Node getRight() {
      return this.right;
    }

    int getValue() {
      return this.value;
    }
    
    
  }

}
class Class {
  public static void main() {
    int[] arr;
    arr = new int[5];
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 5;
    arr[3] = 7;
    arr[4] = 11;

    System.out.println(arr[0]);
    System.out.println(arr[4]); // this will not be visible
    System.out.println(arr[1] < arr[3] /* hahahahahaha */);
    System.out.println(arr[2] == 4);
    System.out.println(arr.length);
  }
}

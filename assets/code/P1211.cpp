import java.util.*;

public class Main {

  public static int check(int x, int n, int[] num) {
    int cnt = 0;
    while (x != 0) {
      boolean f = false;
      for (int i = 0; i < n; ++i) {
        if (x % 10 == num[i]) {
          f = true;
          break;
        }
      }
      if (!f) {
        return 0;
      }
      ++cnt;
      x /= 10;
    }
    return cnt;
  }

  public static void main(String[] args) {
    int[] num = new int[9];
    Scanner cin = new Scanner(System.in);
    int n = cin.nextInt(), cnt = 0;
    for (int i = 0; i < n; ++i) {
      num[i] = cin.nextInt();
    }
    for (int a = 0; a < n; ++a) {
      for (int b = 0; b < n; ++b) {
        for (int c = 0; c < n; ++c) {
          for (int d = 0; d < n; ++d) {
            for (int e = 0; e < n; ++e) {
              int abc = num[a] * 100 + num[b] * 10 + num[c];
              if (check(abc * num[d], n, num) == 3 && check(abc * num[e], n, num) == 3 && check(abc * num[d] * 10 + abc * num[e], n, num) == 4) {
                ++cnt;
              }
            }
          }
        }
      }
    }
    System.out.println(cnt);
  }
}

/*
 * ###################################################################
 * #.................................................................#
 * #.............#......#............Created.By.RBTree...............#
 * #............#.#....#.#........... Limiting-Factor................#
 * #.............########............................................#
 * #............#........#..##############################...........#
 * #...........#..V........V..#..#........................#..#...#...#
 * #............#........#....#..........###..###..........#..#.#.#..#
 * #............#..X##X..#..#............#....#.#...........#..#...#.#
 * #...........#...N##N...#..#...........###..###..........#.........#
 * #.......MOO..#..@.....#....#.#.#.#...................#.#..........#
 * #.............########.....#.#.#.##############.#.#..#.#..........#
 * #..........................#.#.#.#.............#.#.#.#.#..........#
 * #......#########...........#.#.#.#.................#.#.#..........#
 * #.....#.........#..........#.#.#.#.................#.#.#..........#
 * #.#.#.#G#R#A#S#S#.#.#......#.#.#.#.................#.#.#..........#
 * #.###################......#.#.#.#.................#.#.#..........#
 * #...........................#.#.#...................#.#...........#
 * #.................................................................#
 * ###################################################################
 */
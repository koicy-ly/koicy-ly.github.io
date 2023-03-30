import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner cin = new Scanner(System.in);
    int n = cin.nextInt(), m = cin.nextInt(), target = 0;
    if (m % n != 0) {
      System.out.println(-1);
    } else {
      m /= n;
      while ((m & 1) == 0) {
        m >>= 1;
        ++target;
      }
      while ((m % 3) == 0) {
        m /= 3;
        ++target;
      }
      if (m != 1) {
        target = -1;
      }
      System.out.println(target);
    }
    cin.close();
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
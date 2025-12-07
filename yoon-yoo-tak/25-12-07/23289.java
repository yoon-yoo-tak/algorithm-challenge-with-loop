import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        FastScanner scanner = new FastScanner(System.in);

        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int k =  scanner.nextInt();

        Room room = new Room(n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int v =  scanner.nextInt();
                if (v == 0) continue;
                if (1 <= v && v <= 4){
                    Direction dir = null;
                    if (v == 1) dir = Direction.RIGHT;
                    else if (v == 2) dir = Direction.LEFT;
                    else if (v == 3) dir = Direction.UP;
                    else if (v == 4) dir = Direction.DOWN;
                    room.addHeater(new Heater(i, j, dir));
                }else if (v == 5){
                    room.addCell(new Point(i, j));
                }
            }
        }

        int w = scanner.nextInt();

        for (int i = 0; i < w; i++){
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            int t = scanner.nextInt();

            int xx = x - 1;
            int yy = y - 1;

            if (t == 0){
                room.walls.upWall(xx, yy);
            }else{
                room.walls.rightWall(xx, yy);
            }
        }

        GoodByeHeater goodByeHeater = new GoodByeHeater(room, k);

        System.out.println(goodByeHeater.simulate());
    }

    private static class Point{
        int x, y;
        Point(int x, int y){
            this.x = x;
            this.y = y;
        }
    }

    private enum Direction{
        UP(-1, 0),
        DOWN(1, 0),
        RIGHT(0, 1),
        LEFT(0, -1);

        final int dx;
        final int dy;
        Direction(int x, int y){
            this.dx = x;
            this.dy = y;
        }
    }

    private static class Room{
        int x, y;
        int[][] tmp;
        Walls walls;
        List<Heater> heaters = new ArrayList<>();
        List<Point> cells = new ArrayList<>();

        Room(int x, int y){
            this.x = x;
            this.y = y;
            this.tmp = new int[x][y];
            this.walls = new Walls(x, y);
        }

        void addHeater(Heater a){
            heaters.add(a);
        }

        void addCell(Point p){
            cells.add(p);
        }

        boolean inRange(int nx, int ny){
            return 0 <= nx && nx < x && 0 <= ny && ny < y;
        }
    }

    private static class Walls{
        int x, y;
        boolean[][] isUpWalls, isRightWalls;

        Walls(int x, int y){
            this.x = x;
            this.y = y;
            this.isUpWalls = new boolean[x][y];
            this.isRightWalls = new boolean[x][y];
        }

        void upWall(int nx, int ny){
            isUpWalls[nx][ny] = true;
        }

        void rightWall(int nx, int ny){
            isRightWalls[nx][ny] = true;
        }

        boolean canGoUp(int nx, int ny){
            if (nx <= 0) return false;
            return !isUpWalls[nx][ny];
        }

        boolean canGoDown(int nx, int ny){
            if (nx >= x - 1) return false;
            return !isUpWalls[nx + 1][ny];
        }

        boolean canGoRight(int nx, int ny){
            if (ny >= y - 1) return false;
            return !isRightWalls[nx][ny];
        }

        boolean canGoLeft(int nx, int ny){
            if (ny <= 0) return false;
            return !isRightWalls[nx][ny - 1];
        }

        boolean canMove(int x1, int y1, int x2, int y2){
            if (x1 == x2){
                if (y2 == y1 + 1) return canGoRight(x1, y1);
                if (y2 == y1 - 1) return canGoLeft(x1, y1);
            }else if (y1 == y2){
                if (x2 == x1 + 1) return canGoDown(x1, y1);
                if (x2 == x1 - 1) return canGoUp(x1, y1);
            }
            return false;
        }
    }

    private static class Heater{
        int x, y;
        Direction d;

        Heater(int x, int y, Direction d){
            this.x = x;
            this.y = y;
            this.d = d;
        }

        void blow(Room room, int[][] acc){
            int rx = room.x;
            int ry = room.y;

            Walls walls = room.walls;

            boolean[][] visited = new boolean[rx][ry];
            Deque<Wind> q = new ArrayDeque<>();

            int sx = x + d.dx;
            int sy = y + d.dy;
            if (!room.inRange(sx ,sy))
                return;
            if (!walls.canMove(x, y, sx, sy))
                return;

            visited[sx][sy] = true;
            q.add(new Wind(sx, sy , 5));
            acc[sx][sy] += 5;

            while (!q.isEmpty()){
                Wind cur = q.poll();
                if (cur.power <= 1) continue;

                int nPower = cur.power-1;

                switch (d){
                    case RIGHT:
                        if (walls.canGoUp(cur.x, cur.y) && walls.canGoRight(cur.x - 1, cur.y)){
                            int nx = cur.x - 1;
                            int ny = cur.y + 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }

                        if (walls.canGoRight(cur.x, cur.y)){
                            int nx = cur.x;
                            int ny = cur.y+1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }

                        if (walls.canGoDown(cur.x, cur.y) && walls.canGoRight(cur.x + 1, cur.y)){
                            int nx = cur.x + 1;
                            int ny = cur.y + 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        break;
                    case LEFT:
                        if (walls.canGoUp(cur.x, cur.y) && walls.canGoLeft(cur.x - 1, cur.y)){
                            int nx = cur.x - 1;
                            int ny = cur.y - 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoLeft(cur.x, cur.y)){
                            int nx = cur.x;
                            int ny = cur.y - 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoDown(cur.x, cur.y) && walls.canGoLeft(cur.x + 1, cur.y)){
                            int nx = cur.x + 1;
                            int ny =cur.y - 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        break;
                    case UP:
                        if (walls.canGoLeft(cur.x, cur.y) && walls.canGoUp(cur.x, cur.y - 1)){
                            int nx = cur.x - 1;
                            int ny = cur.y - 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoUp(cur.x, cur.y)){
                            int nx = cur.x - 1;
                            int ny =cur.y;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoRight(cur.x, cur.y) && walls.canGoUp(cur.x, cur.y + 1)){
                            int nx = cur.x - 1;
                            int ny = cur.y + 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        break;
                    case DOWN:
                        if (walls.canGoLeft(cur.x, cur.y) && walls.canGoDown(cur.x, cur.y - 1)){
                            int nx = cur.x + 1;
                            int ny =cur.y - 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoDown(cur.x, cur.y)){
                            int nx = cur.x + 1;
                            int ny = cur.y;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        if (walls.canGoRight(cur.x, cur.y) && walls.canGoDown(cur.x, cur.y + 1)){
                            int nx = cur.x + 1;
                            int ny =cur.y + 1;
                            if (room.inRange(nx, ny) && !visited[nx][ny]){
                                visited[nx][ny] = true;
                                acc[nx][ny] += nPower;
                                q.add(new Wind(nx, ny, nPower));
                            }
                        }
                        break;
                }
            }
        }

        private static class Wind {
            int x, y, power;
            Wind(int x, int y, int power){
                this.x = x;
                this.y = y;
                this.power = power;
            }
        }
    }

    private static class GoodByeHeater{
        Room room;
        int k;

        GoodByeHeater(Room room, int k){
            this.room = room;
            this.k = k;
        }

        int simulate(){
            int chocolate = 0;

            while (true){
                blow();

                temperatureChange();

                coolCells();

                chocolate++;

                if (chocolate > 100) {
                    return 101;
                }

                if (allOk()) {
                    return chocolate;
                }
            }
        }

        private void blow(){
            int x = room.x;
            int y = room.y;
            int[][] acc = new int[x][y];

            for (Heater h : room.heaters){
                h.blow(room, acc);
            }

            for (int i = 0; i < x; i++){
                for (int j = 0; j < y; j++){
                    room.tmp[i][j] += acc[i][j];
                }
            }
        }

        private void temperatureChange(){
            int x =  room.x;
            int y = room.y;
            Walls walls = room.walls;

            int[][] diff = new int[x][y];

            for (int i = 0; i < x; i++){
                for (int j = 0; j < y; j++){
                    int cur = room.tmp[i][j];

                    if (j + 1 < y && walls.canGoRight(i, j)){
                        int nxt = room.tmp[i][j + 1];
                        int d = Math.abs(cur - nxt) / 4;
                        if (d > 0){
                            if (cur > nxt){
                                diff[i][j] -= d;
                                diff[i][j + 1] += d;
                            }else{
                                diff[i][j] += d;
                                diff[i][j + 1] -= d;
                            }
                        }
                    }

                    if (i >= 1 && walls.canGoUp(i, j)){
                        int nxt = room.tmp[i - 1][j];
                        int d = Math.abs(cur - nxt) / 4;
                        if (d > 0){
                            if (cur > nxt){
                                diff[i][j] -= d;
                                diff[i - 1][j] += d;
                            }else{
                                diff[i][j] += d;
                                diff[i - 1][j] -= d;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < x; i++){
                for (int j = 0; j < y; j++){
                    room.tmp[i][j] += diff[i][j];
                }
            }
        }

        private void coolCells(){
            int x = room.x;
            int y = room.y;
            for (int i = 0; i <y ;i++){
                if (room.tmp[0][i] > 0) room.tmp[0][i]--;
                if (x - 1 != 0&& room.tmp[x - 1][i] > 0) room.tmp[x - 1][i]--;
            }

            for (int i = 1; i < x - 1; i++){
                if (room.tmp[i][0] > 0)  room.tmp[i][0]--;
                if (y - 1 != 0 && room.tmp[i][y - 1] > 0) room.tmp[i][y - 1]--;
            }
        }

        private boolean allOk(){
            for (Point p : room.cells){
                if (room.tmp[p.x][p.y] < k) return false;
            }
            return true;
        }

    }

    private static class FastScanner {
        private final BufferedReader br;
        private StringTokenizer st;
        FastScanner(InputStream is) {
            br = new BufferedReader(new InputStreamReader(is));
        }
        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                String line = br.readLine();
                if (line == null) return null;
                st = new StringTokenizer(line);
            }
            return st.nextToken();
        }
        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
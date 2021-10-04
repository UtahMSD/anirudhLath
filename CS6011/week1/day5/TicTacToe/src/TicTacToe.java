import java.util.ArrayList;

public class TicTacToe {

    private static ArrayList<Character> board = new ArrayList<Character>();
    private static int playersTurn = 1;

    public static void main(String[] args) {
        for (int i = 0; i < 9; i++) {
            board.add(' ');

        }
    }

}

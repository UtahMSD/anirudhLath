import javax.sound.sampled.LineUnavailableException;
public class MAIN {
    public static void main(String[] args) {
        try {
            Player player = new Player();
            Player.sounds.add(new WhiteNoise());
            Player.sounds.add(new SquareWave(500));
            Player.sounds.add(new SineWave(200));
            Player.filters.add(new volume(1));
            //Player.filters.add(new Reverb(0.2, 11170));
            player.play(0);
        } catch (NullPointerException | LineUnavailableException n) {
            System.out.println(n.getMessage());
            System.exit(-1);
        }
    }
}

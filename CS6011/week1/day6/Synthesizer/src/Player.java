import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.lang.invoke.VolatileCallSite;

public class Player {
    public static Clip c;
    private static AudioComponent sound;
    private static AudioComponent filter;
    private static AudioClip clip;
    private static AudioFormat format;

    private AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
    private AudioFormat format24 = new AudioFormat(44100, 24, 1, true, false);
    private AudioFormat format32 = new AudioFormat(44100, 32, 1, true, false);

    public Player() throws LineUnavailableException {
        c = AudioSystem.getClip();
        format = format16;
        sound = new SineWave(1000);
        filter = new volume(2.1);
        filter.connectInput(sound);
        clip = filter.getClip();
    }

    public void play(int loop) throws LineUnavailableException {
        c.open(format, clip.getData(), 0, clip.getData().length);
        System.out.println("Playing...");
        c.start();
        c.loop(loop + 1);
        while (c.getFramePosition() < AudioClip.TOTAL_SAMPLES || c.isActive() || c.isRunning()) {
        }
        System.out.println("Done playing " + (loop + 1) + " times.");
        c.close();
    }

    public static void main(String[] args) throws LineUnavailableException {
        try {
            Player player = new Player();
            player.play(0);
        } catch (NullPointerException n) {
            System.out.println(n.getMessage());
            System.exit(-1);
        }


    }

}

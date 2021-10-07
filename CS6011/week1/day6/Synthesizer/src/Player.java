import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.lang.invoke.VolatileCallSite;
import java.util.ArrayList;
import java.util.zip.Adler32;

public class Player {
    public static Clip c;
    private static ArrayList<AudioComponent> sounds = new ArrayList<>();
    private static ArrayList<AudioComponent> filters = new ArrayList<>();
    private static AudioComponent mixer;
    private static AudioClip clip;
    private static AudioFormat format;
    private static AudioComponent temp;


    private AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
    private AudioFormat format24 = new AudioFormat(44100, 24, 1, true, false);
    private AudioFormat format32 = new AudioFormat(44100, 32, 1, true, false);

    public Player() throws LineUnavailableException {
        c = AudioSystem.getClip();
        format = format16;

        temp = new SineWave(349);
        sounds.add(temp);

        temp = new SineWave(5000);
        sounds.add(temp);

        temp = new volume(0.5);
        filters.add(temp);

        mixer = new mixer();
        for (AudioComponent filter: filters) {
            for (AudioComponent sound: sounds) {
                filter.connectInput(sound);
                mixer.connectInput(filter);
            }
        }

        clip = mixer.getClip();
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

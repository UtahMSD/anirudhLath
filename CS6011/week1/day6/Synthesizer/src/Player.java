import javax.sound.sampled.*;
import java.util.ArrayList;

public class Player {
    public static Clip c;
    public static ArrayList<AudioComponent> sounds;
    public static ArrayList<AudioComponent> filters;
    private static AudioComponent mixer;
    public static AudioClip clip;
    public static AudioFormat format;
    public static int soundCount_ = 0;

    private AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
    private AudioFormat format24 = new AudioFormat(44100, 24, 1, true, false);
    private AudioFormat format32 = new AudioFormat(44100, 32, 1, true, false);

    public Player() throws LineUnavailableException {
        c = AudioSystem.getClip();
        sounds = new ArrayList<>();
        filters = new ArrayList<>();
        mixer = new mixer();
        clip = new AudioClip();
        format = format16;
    }

    public static void update() {
        mixer = new mixer();
        for (AudioComponent sound : sounds) {
            if (filters.size() > 0) {
                for (AudioComponent filter : filters) {
                    filter.connectInput(sound);
                    mixer.connectInput(filter);
                }
            } else {
                mixer.connectInput(sound);
            }
        }
        clip = mixer.getClip();
    }

    public static void play(int loop) throws LineUnavailableException {
        //update();
        c.open(format, clip.getData(), 0, clip.getData().length);
        System.out.println("Playing...");
        c.start();
        c.loop(loop);
//        while (c.getFramePosition() < AudioClip.TOTAL_SAMPLES || c.isActive() || c.isRunning()) {
//        }
//        System.out.println("Done playing " + (loop + 1) + " times.");
//        c.close();
    }

    public static void replay(int loop) throws LineUnavailableException {
        c.stop();
        c.close();
        //update();
        play(loop);
    }
}

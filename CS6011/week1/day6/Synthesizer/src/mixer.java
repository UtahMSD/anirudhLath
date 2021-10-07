import javax.sound.midi.Soundbank;
import java.lang.reflect.Array;
import java.util.ArrayList;

public class mixer implements AudioComponent {

    ArrayList<AudioClip> inputClips = new ArrayList<>();

    @Override
    public AudioClip getClip() {
        AudioClip result = new AudioClip();
        for (int i = 0; i < inputClips.size(); i++) {
            if (inputClips.get(i) == null) {
                throw new NullPointerException("Please connect the input to the source and rerun the program.");
            } else {
                System.out.println("Mixing track " + (i + 1) + "...");
                if (i == 0) {
                    for (int j = 0; j < inputClips.get(i).samplesArray.length; j++) {
                        result.setSample(j, (short) (inputClips.get(i).samplesArray[j] / inputClips.size()));
                    }
                } else {
                    for (int j = 0; j < inputClips.get(i).samplesArray.length; j++) {
                        result.setSample(j, (short) ((result.samplesArray[j] + inputClips.get(i).samplesArray[j]) / inputClips.size()));
                    }
                }
            }
        }
        System.out.println("Final track ready!");
        return result;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        if (hasInput()) {
            inputClips.add(input.getClip());
            System.out.println("Added track " + inputClips.size() + " to the mixer!");
        } else {
            System.out.println("This class does not accept inputs.");
            System.exit(-1);
        }
    }
}

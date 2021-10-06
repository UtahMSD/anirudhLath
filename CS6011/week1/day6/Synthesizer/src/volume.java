public class volume implements AudioComponent {

    AudioClip inputClip = null;
    double volume = 1.0;

    @Override
    public AudioClip getClip() {
        AudioClip result = new AudioClip();
        if (inputClip == null) {
            throw new NullPointerException("Please connect the input to the source and rerun the program.");
        } else {
            for (int i = 0; i < inputClip.samplesArray.length; i++) {
                result.setSample(i, (short) (volume * inputClip.samplesArray[i]));
            }
        }
        return result;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        if (hasInput()) {
            inputClip = input.getClip();
        }
    }

    public volume(double amp) {
        volume = Math.max(0, Math.min(1, amp));
    }
}

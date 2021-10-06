public class SineWave implements AudioComponent {
    int frequency;

    @Override
    public AudioClip getClip() {
        AudioClip clip = new AudioClip();
        for (int i = 0; i < clip.samplesArray.length; i++) {
            clip.setSample(i,
                    (short) (Short.MAX_VALUE * Math.sin(2 * Math.PI * frequency * i / AudioClip.sampleRate))); //
            // Configured for a sine wave of int frequency, the highest possible amplitude.

        }
        return clip;
    }

    @Override
    public boolean hasInput() {
        return false;
    }

    @Override
    public void connectInput(AudioComponent input) {
        assert hasInput();
    }

    public SineWave(int f) {
        frequency = f;
    }
}

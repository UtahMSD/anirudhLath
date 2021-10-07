public class VFSineWave implements AudioComponent{

    AudioClip inputClip = null;

    @Override
    public AudioClip getClip() {
        AudioClip clip = new AudioClip();
        double phase = 0.0;
        for (int i = 0; i < clip.samplesArray.length; i++) { // Configured for a square wave of int frequency, the
            // highest possible amplitude.
            phase += (2 * Math.PI * inputClip.getSample(i)) / inputClip.samplesArray.length;
            clip.setSample(i, (short) (Short.MAX_VALUE * Math.sin(phase)));
//            if (((float) (frequency * i * 2 / AudioClip.sampleRate)) % 2 > 0.5) { // ((float)(frequency * i * 2 /
//                // AudioClip.sampleRate)) % 2 was always equal to zero, therefore I used 2 to make the algorithm work
//                // and multiplied 2 to the frequency to compensate for the %2.
//                clip.setSample(i, Short.MAX_VALUE);
//            } else {
//                clip.setSample(i, Short.MIN_VALUE);
//            }
        }
        return clip;
    }

    @Override
    public boolean hasInput() {
        return true;
    }

    @Override
    public void connectInput(AudioComponent input) {
        if (hasInput()) {
            inputClip = input.getClip();
        } else {
            System.out.println("This class does not accept inputs.");
            System.exit(-1);
        }
    }
}

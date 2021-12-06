using FMODUnity;
using UnityEngine;

public class PedalHiHat : AbstractInstrument
{
    FMOD.Studio.EventInstance instance;

    [EventRef]
    public string eventName = "";

    [SerializeField]
    HandleInput input;

    [SerializeField]
    HiHat hiHat;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling snare Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);

        input.updateHiHatOpen(input.getHiHatOpen() > 0.5f ? 0.0f : 1.0f);
        instance.setParameterByName("Open", input.getHiHatOpen());

        instance.start();
        hiHat.EnqueueSound(instance);
    }

    public void ReproduceClose(float strength)
    {
        Debug.Log("Calling snare Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("Open", 0);
        instance.start();
        instance.release();
    }
}

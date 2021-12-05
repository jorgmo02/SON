using FMODUnity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PedalHiHat : AbstractInstrument
{
    FMOD.Studio.EventInstance instance;

    [EventRef]
    public string eventName = "";

    [SerializeField]
    HandleInput input;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling snare Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);

        input.updateHiHatOpen(input.getHiHatOpen() > 0.5f ? 0.0f : 1.0f);
        instance.setParameterByName("Open", input.getHiHatOpen());

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

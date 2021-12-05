using FMODUnity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HiHat : AbstractInstrument
{
    FMOD.Studio.EventInstance instance;

    [EventRef]
    public string eventName = "";

    [SerializeField]
    HandleInput input;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling Hi Hat Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("Open", input.getHiHatOpen());

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

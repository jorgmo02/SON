using FMODUnity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snare : AbstractInstrument
{
    [EventRef]
    public string eventName = "";

    FMOD.Studio.EventInstance instance;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling snare Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("DistanceToCenter", CalculateDistance(hitPos));

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

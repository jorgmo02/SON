using FMODUnity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Drum : AbstractInstrument
{
    [EventRef]
    public string eventName = "";

    FMOD.Studio.EventInstance instance;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("DistanceToCenter", CalculateDistance(hitPos));

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

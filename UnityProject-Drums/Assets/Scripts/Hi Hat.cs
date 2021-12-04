using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HiHat : AbstractInstrument
{
    FMOD.Studio.EventInstance instance;
    [SerializeField] [Range (0f,1f)] float open = 0.5f;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling Hi Hat Reproduce");

        instance = FMODUnity.RuntimeManager.CreateInstance("event:/Drums/HiHat");

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("Open", open);

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

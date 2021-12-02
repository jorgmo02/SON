using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snare : AbstractInstrument
{
    [SerializeField]
    FMODUnity.StudioEventEmitter fmodEventEmitter;

    FMOD.Studio.EventInstance instance;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling snare Reproduce");

        //fmodEventEmitter.SetParameter("Strength", strength);

        //fmodEventEmitter.Play();

        Vector2 hitRelativeToCenter = hitPos - new Vector2(transform.position.x, transform.position.y);

        Debug.Log(hitRelativeToCenter);

        hitRelativeToCenter.x /= transform.parent.transform.localScale.x/2;
        hitRelativeToCenter.y /= transform.parent.transform.localScale.y/2;

        float mod = Mathf.Sqrt(hitRelativeToCenter.sqrMagnitude);

        Debug.Log(mod);
        
        instance = FMODUnity.RuntimeManager.CreateInstance("event:/Drums/Snare");

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("DistanceToCenter", mod);

        instance.start();

        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        instance.release();
    }
}

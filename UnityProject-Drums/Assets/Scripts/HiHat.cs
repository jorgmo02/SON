using FMODUnity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HiHat : AbstractInstrument
{
    //FMOD.Studio.EventInstance instance;

    Queue<FMOD.Studio.EventInstance> instances; 

    [EventRef]
    public string eventName = "";

    [SerializeField]
    HandleInput input;

    private void Awake()
    {
        instances = new Queue<FMOD.Studio.EventInstance>();
    }

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling Hi Hat Reproduce");

        var instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("Open", input.getHiHatOpen());

        instance.start();
        instances.Enqueue(instance);
        Invoke("ReleaseInstance", 5);
    }

    void ReleaseInstance()
    {
        // la libero para que se vuelva independiente y se destruya asi misma al terminar
        if (instances.Count > 0)
        {
            var inst = instances.Dequeue();
            if (inst.isValid())
                inst.release();
        }
    }

    public void CloseHiHat(float strength)
    {
        while (instances.Count > 0)
        {
            var inst = instances.Dequeue();
            if (inst.isValid())
                inst.stop(FMOD.Studio.STOP_MODE.IMMEDIATE);
            else Debug.LogError("Instance not valid, cannot stop");
            inst.release();
        }

        Reproduce(Vector2.zero, strength);
    }
}

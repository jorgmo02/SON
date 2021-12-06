using FMODUnity;
using Nito.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HiHat : AbstractInstrument
{
    //FMOD.Studio.EventInstance instance;

    Deque<FMOD.Studio.EventInstance> instances; 

    [EventRef]
    public string eventName = "";

    [SerializeField]
    HandleInput input;

    private void Awake()
    {
        instances = new Deque<FMOD.Studio.EventInstance>();
    }

    public void EnqueueSound(FMOD.Studio.EventInstance instance)
    {
        instances.AddToBack(instance);
        if (instances.Count > 100)
        {
            var a = instances.RemoveFromFront();
            a.stop(FMOD.Studio.STOP_MODE.IMMEDIATE);
            a.release();
        }
    }

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling Hi Hat Reproduce");

        var instance = FMODUnity.RuntimeManager.CreateInstance(eventName);

        instance.setParameterByName("Strength", strength);
        instance.setParameterByName("Open", input.getHiHatOpen());

        instance.start();
        EnqueueSound(instance);
        //instance.release();
    }

    public void CloseHiHat(float strength)
    {
        while (instances.Count > 0)
        {
            var inst = instances.RemoveFromFront();
            inst.stop(FMOD.Studio.STOP_MODE.IMMEDIATE);
            inst.release();
        }

        Reproduce(Vector2.zero, strength);
    }
}

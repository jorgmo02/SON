using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snare : AbstractInstrument
{
    //[SerializeField]
    //... fmodComponent;

    public override void Reproduce(Vector2 hitPos, float strength)
    {
        
        Debug.Log("Calling snare Reproduce");
    }
}

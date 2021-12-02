using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AbstractInstrument : MonoBehaviour
{
    public virtual void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling default Reproduce");
    }
}

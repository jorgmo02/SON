using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class AbstractInstrument : MonoBehaviour
{
    public virtual void Reproduce(Vector2 hitPos, float strength)
    {
        Debug.Log("Calling default Reproduce");
    }

    public float CalculateDistance(Vector2 pos)
    {
        Vector2 hitRelativeToCenter = pos - new Vector2(transform.position.x, transform.position.y);

        Debug.Log(hitRelativeToCenter);

        hitRelativeToCenter.x /= transform.lossyScale.x / 2f;
        hitRelativeToCenter.y /= transform.lossyScale.y / 2f;

        return Mathf.Sqrt(hitRelativeToCenter.sqrMagnitude);
    }
}

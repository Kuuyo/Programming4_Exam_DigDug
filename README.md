# Small 2D Engine with DigDug

2D Game Engine with DigDug as demo game

## 3rd Party libraries:
- [GLM](https://github.com/g-truc/glm)
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [Box2D](https://github.com/erincatto/Box2D)

## Big influences:
- OverlordEngine
- Unity
- https://bell0bytes.eu/game-programming/
- http://www.gameprogrammingpatterns.com/

## Some Engine specifics

GAMELOOP
-------------------------------------------------
-------------------------------------------------
[Input] : First of all the Input is processed
-------------------------------------------------
- This supports both keyboard and any device XInput supports.
- XInput controllers work up to 4 devices.
- InputMappings are a struct that get stored in a map.
 > InputMapping Struct
 	These are ID'd by a string, support keyboard axises, GamePad
 	Axises, Single buttons, hold a state of type KeyState
- Checking Input is very much like OverlordEngine/Unity
 > GetInputMappingStruct(string name) -> returns the full struct
 > GetInputMappingState(string name) -> returns KeyState
 > GetInputMappingAxis(string name) -> returns axis range(-1,1)
- It also provides many other functions.
-------------------------------------------------
[FixedUpdate] : Because slow computers are a thing
-------------------------------------------------
- The FixedUpdate is the update where the Physics happen.
- This is simulated by Box2D.
- Runs at 60 frames per second
- Catches up to a max of 10 catch-up-loops
-------------------------------------------------
[Update] : The familiar friend
-------------------------------------------------
- Pretty straight-forward, no strings attached
-------------------------------------------------
[LateUpdate] : Only one of these
-------------------------------------------------
When something needs to happen after something has happened
while still in the same frame
-------------------------------------------------
[DestroyUpdate] : Safety first
-------------------------------------------------
Destroys anything that is marked for deletion, safely outside
the updates, but before the rendering happens.
-------------------------------------------------
[Render] : Just a black screen could be a boring game
-------------------------------------------------
The renderer pretty much only renders the Texture2Ds in the
current scene, generated by several Components to avoid
every component having a Render function.
(No component has a Render function)

V-Sync is on by default, constricting the entire loop to your
screen's vertical sync rate.

LOGGING
-------------------------------------------------
Logging is done by using the macro's

- LogFormatC(lvl, msg, ...)
- LogInfoC(msg)
- LogDebugC(msg)
- LogWarningC(msg)
- LogErrorC(msg)

Of course you can also use dae::Log::GetInstance() and use the
functions from there, but the macros already fill in the caller
variable with __FUNCTION__, so there's no need to pass where
the logger is being called from.
This had to be done through a macro, as __FUNCTION__ uses the
function it was called in.

GameObject
-------------------------------------------------
This is your lifeline in this engine.
A class which is final, consisting of Components.

There is no TransformComponent, as this would never be
removed or "added".
It would be silly to call a GetComponent<TransformComponent>()
everytime one needs the Transform.
Therefore the classic transform functions are immediately
available on the GameObject.

GameObjects can also have Children.

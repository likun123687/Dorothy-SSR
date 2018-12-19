Dorothy builtin.Platformer
{store:Store} = Data
AlignNode = require "UI.Control.Basic.AlignNode"
Rectangle = require "UI.View.Shape.Rectangle"
Circle = require "UI.View.Shape.Circle"
Star = require "UI.View.Shape.Star"
CircleButton = require "UI.Control.Basic.CircleButton"

keyboardEnabled = false
controlPlayer = "KidW"
playerGroup = Group {"player"}
updatePlayerControl = (key,flag)->
	player = nil
	playerGroup\each => player = @ if @unit.tag == controlPlayer
	player[key] = flag if player
uiScale = App.designScale

with AlignNode true
	.visible = false
	\addChild with AlignNode!
		.hAlign = "Left"
		.vAlign = "Bottom"
		\addChild with Menu!
			\addChild with CircleButton {
					text: "Left"
					x: 20*uiScale
					y: 60*uiScale
					radius: 30*uiScale
					fontSize: 18*uiScale
				}
				.anchor = Vec2.zero
				\slot "TapBegan",-> updatePlayerControl "keyLeft",true
				\slot "TapEnded",-> updatePlayerControl "keyLeft",false
			\addChild with CircleButton {
					text: "Right"
					x: 90*uiScale
					y: 60*uiScale
					radius: 30*uiScale
					fontSize: 18*uiScale
				}
				.anchor = Vec2.zero
				\slot "TapBegan",-> updatePlayerControl "keyRight",true
				\slot "TapEnded",-> updatePlayerControl "keyRight",false
	\addChild with AlignNode!
		.hAlign = "Right"
		.vAlign = "Bottom"
		\addChild with Menu!
			\addChild with CircleButton {
					text: "Jump"
					x: -80*uiScale
					y: 60*uiScale
					radius: 30*uiScale
					fontSize: 18*uiScale
				}
				.anchor = Vec2.zero
				\slot "TapBegan",-> updatePlayerControl "keyUp",true
				\slot "TapEnded",-> updatePlayerControl "keyUp",false
			\addChild with CircleButton {
					text: "Shoot"
					x: -150*uiScale
					y: 60*uiScale
					radius: 30*uiScale
					fontSize: 18*uiScale
				}
				.anchor = Vec2.zero
				\slot "TapBegan",-> updatePlayerControl "keyShoot",true
				\slot "TapEnded",-> updatePlayerControl "keyShoot",false
	\addTo with Director.ui
		.renderGroup = true

keyboardControl = loop ->
	return unless keyboardEnabled
	updatePlayerControl "keyLeft", Keyboard\isKeyPressed "A"
	updatePlayerControl "keyRight", Keyboard\isKeyPressed "D"
	updatePlayerControl "keyUp", Keyboard\isKeyPressed "K"
	updatePlayerControl "keyShoot", Keyboard\isKeyPressed "J"

gameEnded = false
thread -> Store.world\slot "Cleanup",-> gameEnded = true
threadLoop ->
	keyboardControl!
	gameEnded

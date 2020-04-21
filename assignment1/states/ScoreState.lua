--[[
    ScoreState Class
    Author: Colton Ogden
    cogden@cs50.harvard.edu

    A simple state used to display the player's score before they
    transition back into the play state. Transitioned to from the
    PlayState when they collide with a Pipe.
]]

ScoreState = Class{__includes = BaseState}

--[[
    When we enter the score state, we expect to receive the score
    from the play state so we know what to render to the State.
]]

-- thanks to Chee Yew Lim for medal graphics
local bronze = love.graphics.newImage('Bronze.png')
local silver = love.graphics.newImage('Silver medal ver2.png')
local gold = love.graphics.newImage('Gold.png')

function ScoreState:enter(params)
    self.score = params.score
end

function ScoreState:update(dt)
    -- go back to play if enter is pressed
    if love.keyboard.wasPressed('enter') or love.keyboard.wasPressed('return') then
        gStateMachine:change('countdown')
    end
end

function ScoreState:render()
    -- simply render the score to the middle of the screen
    love.graphics.setFont(flappyFont)
    love.graphics.printf('Oof! You lost!', 0, 64, VIRTUAL_WIDTH, 'center')

    love.graphics.setFont(mediumFont)
    love.graphics.printf('Score: ' .. tostring(self.score), 0, 100, VIRTUAL_WIDTH, 'center')
    if self.score >= 0 and self.score <= 3 then
        love.graphics.draw(bronze, (VIRTUAL_WIDTH/2) - 13, 120)
    elseif self.score > 3 and self.score <= 5 then
        love.graphics.draw(silver, (VIRTUAL_WIDTH/2) - 13, 120)
    else
        love.graphics.draw(gold, (VIRTUAL_WIDTH/2) - 13, 120)       
    end

    love.graphics.printf('Press Enter to Play Again!', 0, 160, VIRTUAL_WIDTH, 'center')
end
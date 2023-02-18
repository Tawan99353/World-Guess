const categoryButtons = document.querySelectorAll(".category-btn");
const startContainer = document.getElementById("start-container");
const gameContainer = document.getElementById("game-container");
const categoryHeading = document.getElementById("category");

categoryButtons.forEach(button => {
	button.addEventListener("click", () => {
		const category = button.getAttribute("data-category");
		categoryHeading.textContent = `Category: ${category}`;
		startContainer.style.display = "none";
		gameContainer.style.display = "block";
	});
});



const categories = {
	fruits: ['apple', 'banana', 'cherry', 'date', 'elderberry', 'fig', 'grape', 'honeydew', 'kiwi', 'lemon', 'mango', 'orange', 'pear', 'quince', 'raspberry', 'strawberry', 'tangerine', 'watermelon'],
	animals: ['alligator', 'bear', 'cheetah', 'dolphin', 'elephant', 'flamingo', 'giraffe', 'hippopotamus', 'iguana', 'jaguar', 'kangaroo', 'lion', 'moose', 'narwhal', 'octopus', 'penguin', 'rhinoceros', 'seagull', 'toucan', 'zebra'],
	colors: ['black', 'blue', 'brown', 'green', 'grey', 'orange', 'pink', 'purple', 'red', 'turquoise', 'white', 'yellow']
};

let category, currentWord, scrambledWord;

function newWord() {
	category = Object.keys(categories)[Math.floor(Math.random() * Object.keys(categories).length)];
	currentWord = categories[category][Math.floor(Math.random() * categories[category].length)];
	scrambledWord = currentWord.split('').sort(() => 0.5 - Math.random()).join('');
	document.getElementById('scrambled-word').textContent = scrambledWord;
	document.getElementById('category').textContent = `Category: ${category.charAt(0).toUpperCase() + category.slice(1)}`;
	document.getElementById('result').textContent = '';
	document.getElementById('guess-input').value = '';
    
}

function guessWord() {
	const guess = document.getElementById('guess-input').value;
	if (guess === currentWord) {
		document.getElementById('result').textContent = 'Correct!';
		document.getElementById('result').classList.add('correct');
        result.textContent = "Correct!";
        result.style.color = "green";
        wordImage.src = `images/${categories}.png`;
        wordImage.alt = word;
        guessInput.disabled = true;
        guessBtn.disabled = true;
        newWordBtn.disabled = false;
	} else {
		document.getElementById('result').textContent = 'Incorrect. Try again.';
        result.textContent = "Incorrect. Please try again.";
        result.style.color = "red";
	}
	// Reset the game after the user submits their guess
	setTimeout(() => {
		newWord();
		document.getElementById('result').classList.remove('correct');
        
	}, 2000);
 function selectCategory() {
        category = categorySelect.value;
        categoryIndex = categories.indexOf(category);
        if (categoryIndex === -1) {
            alert("Invalid category");
            return;
        }
        words = wordsList[categoryIndex].split(",");
        newWord();
        gameContainer.style.display = "block";
        startContainer.style.display = "none";
}
    
    
  
    
}

document.getElementById('guess-btn').addEventListener('click', guessWord);
document.getElementById('new-word-btn').addEventListener('click', newWord);

document.getElementById('start-btn').addEventListener('click', () => {
	document.getElementById('game-container').style.display = 'block';
	document.getElementById('start-btn').style.display = 'none';
	newWord();
});

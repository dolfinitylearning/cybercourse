/**
 * Data models. There are constructors, and containers. 
 * 
 * The constructors use null as MT for all properties.
 * 
 * Containers are arrays. They use nid as the index. This is repeated data,
 * since the same values are properties of the elements in the arrays.
 * 
 */

var app = app || {};

/**
 * Constructor.
 */
app.RubricItem = function() {
  this.rubricItemNid = null;
  this.title = null;
  //Array of "good" comments from the server. Simple strings.
  //Order matters - matches server order.
  this.good = new Array();
  //Array of new comments created by the user. 
  //See NewRubricComment below.
  this.goodNewComments = Array();
  //Array of "needs work" comments. 
  this.needsWork = new Array();
  //Array of new comments created by the user. 
  this.needsWorkNewComments = Array();
  //Array of "poor" comments. 
  this.poor = new Array();
  //See NewRubricComment below.
  this.poorNewComments = Array();
  this.notes = null;
};

/**
 * Contains all rubric items fetched during grading. Used as cache.
 * Index is nid.
 * @type Array
 */
app.allRubricItems = new Array();

/**
 * Constructor for new comment objects, created by the user.
 */
app.NewRubricComment = function() {
  this.comment = null;
//  this.commentRating = null;
  this.saveFlag = null;
}

/**
 * Constructor.
 */
app.ModelSolution = function() {
  this.modelSolutionNid = null;
  //Exercise this is for.
  this.exerciseNid = null;
  //HTML for the solution, including links to files.
  this.renderedSolution = null;
  this.notes = null;
};

/**
 * Contains all model solutions fetched during grading. Used as cache.
 * Index is nid.
 * @type Array
 */
app.allModelSolutions = new Array();

/**
 * Constructor.
 */
app.Exercise = function() {
  this.exerciseNid = null;
  this.title = null;
  //HTML for exercise body, including links to files.
  this.renderedExercise = null;
  //Array of nids of rubric items used to assess this exercise.
  this.rubricItems = new Array();
  //Array of nids for model solution.
  this.modelSolutions = new Array();
  //Notes for authors, instructors, and graders.
  this.notes = null;
};

/**
 * Contains all exercises fetched during grading. Used as cache.
 * Index is nid.
 * @type Array
 */
app.allExercises = new Array();

app.Submission = function() {
  this.submissionNid = null;
  //Exercise this is for.
  this.exerciseNid = null;
  //Student's uid.
  this.studentUid = null;
  //HTML for the solution, including links to files.
  this.renderedSolution = null;
  //When it was submitted.
  this.whenSubmitted = null;
  //Feedback message for this submission.
  this.feedback = null;
  //Exercise complete?
  this.complete = null;
  //Feedback sent?
  this.feedbackSent = null;
  //Rubric item selections.
  this.rubricItemSelections = new Array();
};

/**
 * Constructor for grader's decision on a rubric item for a submission.
 * Instances go in submission.rubricItemSelections.
 */
app.RubricItemSelection = function() {
  this.rubricItemNid = null;
  this.comment = null;
  this.commentRating = null;
};

/**
 * Submissions to grade. Submission nid is index. 
 * @type Array
 */
app.submissionsToGrade = new Array();

app.Student = function() {
  this.studentUid = null;
  //First and last name.
  this.name = null;
  //Group(s) the student is in. Array of group ids.
  this.groups = new Array();
};

/**
 * Contains all student data fetched during grading. Used as cache.
 * key is nid.
 * @type Array
 */
app.allStudents = new Array();

/**
 * Constructor for one group object.
 */
app.Group = function() {
  this.groupId = null;
  this.title = null;
};

/**
 * Container all group data.
 * @type Array
 */
app.allGroups = new Array();
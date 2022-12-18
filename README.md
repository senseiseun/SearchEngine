<h1>COVID Search Engine</h1>
<p>Seun Suberu</p>
Info: Data Structures Final Project at Southern Methodist University. Remade on December 2022. <a href="https://github.com/senseisub/SearchEngine">Remodel of original project.</a>
<h2>Kick Covid in the Ass</h2>
<h3>Description</h3>
<p>This is a COVID Document Search Engine written in C++ and built using CMAKE that utilizes a self-implemented AVLTree for word storage and self-implemented HashTable for authors.
The documents are ranked by term-frequency/inverse document frequency metric and indexed into self-made data structures. There is a command line user interface provided. Implemented own Hash Table and AVL Tree to store authors and stemmed words.
</p>

<h3>How to use</h3>
<p>Set up: <br>
    <a href = "https://www.semanticscholar.org/cord19/download">Link to Dataset for covid information files</a>
</p>
<p>
    Program argument should be then a path to the directory where the files for indexing are located.
    <br>
    For example:<br>

    $ mkdir build
    $ cmake ..
    $ ./SearchEngine {directory}
</p>
<p>
    From there the program should run as expected. The program loads and indexes all the files and then the program should be ready for any queries.
    The keywords recognized by this Search Engine are "AUTHOR", "AND", "OR", and "NOT". 
    The only keywords that can appear at the beginning of a query are AUTHOR and NOT. The other have to be have a search word before and after.<br>
    AUTHOR: returns all results of particular author, but when AUTHOR is preceded by a word then the results are documents that contain that word from that author.<br>
    AND: Returns documents that contain the words before and after the KEYWORD.<br>
    OR: Returns documents that contain either the word before or the one after.<br>
    NOT: Returns all documents that do not contain the particular word. Can be compounded with AND or ORs, but had to be the last keyword used in the query and cannot be the only query.<br> 
    <br>
    Examples (THESE QUERIES ARE NOT GUARANTEED TO RETURN RESULTS):

    AUTHOR Suess
</p>
<p>

    covid AND chicken
</p>
<p>

    coronavirus OR pizza
</p>
<p>

    pizza NOT covid
</p>
<p>

    pizza AUTHOR grant
</p>
<p>

    pizza
</p>

<h3>HashTable</h3>
<p> 
    <b>Co-Written and Co-Implemented by Seun Suberu </b><br>
    Used for storing and retrieving author information.
</p>

<h3>HashSet</h3>
<p> 
    <b>Written and Implemented by Seun Suberu </b><br>
    Used for storing and retrieving stop word values.
</p>

<h3>AVLTree</h3>
<p> 
    <b>Written and Implemented by Seun Suberu </b><br>
    Used for storing and retrieving stemmed words with their associated document identifiers for indexing.
</p>

<h3>Article Class</h3>
<p> 
    <b>Written and Implemented by Seun Suberu </b><br>
    Used for storing and retrieving document information.
</p>

<h3>Author Class</h3>
<p> 
    <b>Written and Implemented by Seun Suberu </b><br>
    Used for storing and retrieving author information.
</p>

<h3>Word Class</h3>
<p> 
    <b>Written and Implemented by Seun Suberu </b><br>
    Wrapper class for stemmed word which also contains a collection of InnerDoc objects for keeping track of documents that contain the stemmed word.
</p>



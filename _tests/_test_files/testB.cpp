#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/sql/sql.h"
#include "../../includes/table/table.h"
#include "../../includes/table/typedefs.h"
//------------------------------------------------------------------------------------------

using namespace std;

bool test_stub(bool debug = false)
{
  SQL sql;
  Table t;
  sql.command("make table myTable fields fname, lname, age, id");
  for(int i = 0; i < 200; i++){
    string str = "insert into myTable values scooter,   mcstudent,           " + to_string(i%30)+ ",       " + to_string(i);
    sql.command(str);
  }
  cout << sql.command("select * from myTable") << endl << endl;
  cout << sql.command("select id, age from myTable where age < 2 and fname >= scooter and lname = mcstudent") << endl << endl;
  return true;
}

bool test_interactive(bool debug = false){
  vectorstr commandList = {
    "make table scientists fields FIRST, LAST, YEAR, INVENTION, NATIONALITY",
    "insert into scientists values \"Albert\", \"Einstein\", \"1879\", \"Relativity\", \"German\"",
    "insert into scientists values \"Isaac\", \"Newton\", \"1643\", \"Gravity\", \"English\"",
    "insert into scientists values \"Nikola\", \"Tesla\", \"1856\", \"AC electricity\", \"Serbian\"",
    "insert into scientists values \"Marie\", \"Curie\", \"1867\", \"Radioactivity\", \"Polish\"",
    "insert into scientists values \"Thomas\", \"Edison\", \"1847\", \"Light bulb\", \"American\"",
    "insert into scientists values \"Alexander\", \"Fleming\", \"1881\", \"Penicillin\", \"Scottish\"",
    "insert into scientists values \"Galileo\", \"Galilei\", \"1564\", \"Telescopic astronomy\", \"Italian\"",
    "insert into scientists values \"Charles\", \"Darwin\", \"1809\", \"Evolution\", \"English\"",
    "insert into scientists values \"Louis\", \"Pasteur\", \"1822\", \"Pasteurization\", \"French\"",
    "insert into scientists values \"James\", \"Watt\", \"1736\", \"Steam engine\", \"Scottish\"",
    "insert into scientists values \"Michael\", \"Faraday\", \"1791\", \"Electromagnetism\", \"English\"",
    "insert into scientists values \"Gregor\", \"Mendel\", \"1822\", \"Genetics\", \"Austrian\"",
    "insert into scientists values \"Sigmund\", \"Freud\", \"1856\", \"Psychoanalysis\", \"Austrian\"",
    "insert into scientists values \"Niels\", \"Bohr\", \"1885\", \"Quantum mechanics\", \"Danish\"",
    "insert into scientists values \"Leonardo\", \"da Vinci\", \"1452\", \"Renaissance inventions\", \"Italian\"",
    "insert into scientists values \"Aristotle\", \"NA\", \"0384 BC\", \"Philosophy\", \"Greek\"",
    "insert into scientists values \"Euclid\", \"NA\", \"0300 BC\", \"Geometry\", \"Greek\"",
    "insert into scientists values \"Archimedes\", \"NA\", \"0287 BC\", \"Physics\", \"Greek\"",
    "insert into scientists values \"Pythagoras\", \"NA\", \"0570 BC\", \"Mathematics\", \"Greek\"",
    "insert into scientists values \"Johannes\", \"Kepler\", \"1571\", \"Planetary motion\", \"German\"",
    "insert into scientists values \"Carl\", \"Linnaeus\", \"1707\", \"Taxonomy\", \"Swedish\"",
    "insert into scientists values \"James\", \"Clerk Maxwell\", \"1831\", \"Electromagnetic theory\", \"Scottish\"",
    "insert into scientists values \"Dmitri\", \"Mendeleev\", \"1834\", \"Periodic table\", \"Russian\"",
    "insert into scientists values \"Antoine\", \"Lavoisier\", \"1743\", \"Chemistry\", \"French\"",
    "insert into scientists values \"Max\", \"Planck\", \"1858\", \"Quantum theory\", \"German\"",
    "insert into scientists values \"Enrico\", \"Fermi\", \"1901\", \"Nuclear reactor\", \"Italian\"",
    "insert into scientists values \"Richard\", \"Feynman\", \"1918\", \"Quantum electrodynamics\", \"American\"",
    "insert into scientists values \"Erwin\", \"Schrodinger\", \"1887\", \"Wave mechanics\", \"Austrian\"",
    "insert into scientists values \"Werner\", \"Heisenberg\", \"1901\", \"Uncertainty principle\", \"German\"",
    "insert into scientists values \"Robert\", \"Hooke\", \"1635\", \"Elasticity\", \"English\"",
    "insert into scientists values \"Henry\", \"Cavendish\", \"1731\", \"Hydrogen\", \"English\"",
    "insert into scientists values \"Joseph\", \"Priestley\", \"1733\", \"Oxygen\", \"English\"",
    "insert into scientists values \"Alfred\", \"Nobel\", \"1833\", \"Dynamite\", \"Swedish\"",
    "insert into scientists values \"Hans\", \"Christian Orsted\", \"1777\", \"Electromagnetism\", \"Danish\"",
    "insert into scientists values \"Alessandro\", \"Volta\", \"1745\", \"Electric battery\", \"Italian\"",
    "insert into scientists values \"Guglielmo\", \"Marconi\", \"1874\", \"Radio\", \"Italian\"",
    "insert into scientists values \"Wernher\", \"von Braun\", \"1912\", \"Rocketry\", \"German\"",
    "insert into scientists values \"Tim\", \"BernersLee\", \"1955\", \"World Wide Web\", \"English\"",
    "insert into scientists values \"Steve\", \"Jobs\", \"1955\", \"Personal computer\", \"American\"",
    "insert into scientists values \"Bill\", \"Gates\", \"1955\", \"Software\", \"American\"",
    "insert into scientists values \"George\", \"Washington Carver\", \"1864\", \"Crop rotation\", \"American\"",
    "insert into scientists values \"Rosalind\", \"Franklin\", \"1920\", \"DNA structure\", \"English\"",
    "insert into scientists values \"John\", \"Bardeen\", \"1908\", \"Transistor\", \"American\"",
    "insert into scientists values \"Hedy\", \"Lamarr\", \"1914\", \"Frequency hopping\", \"Austrian\"",
    "insert into scientists values \"Ada\", \"Lovelace\", \"1815\", \"Computer programming\", \"English\"",
    "insert into scientists values \"Alan\", \"Turing\", \"1912\", \"Computing\", \"English\"",
    "insert into scientists values \"Grace\", \"Hopper\", \"1906\", \"Compiler\", \"American\"",
    "insert into scientists values \"Robert\", \"Noyce\", \"1927\", \"Integrated circuit\", \"American\"",
    "insert into scientists values \"Leonard\", \"Kleinrock\", \"1934\", \"Packet switching\", \"American\"",
    "insert into scientists values \"Claude\", \"Shannon\", \"1916\", \"Information theory\", \"American\"",
    "insert into scientists values \"John\", \"von Neumann\", \"1903\", \"Computer architecture\", \"Hungarian\"",
    "insert into scientists values \"Stephen\", \"Hawking\", \"1942\", \"Black holes\", \"English\"",
    "insert into scientists values \"George\", \"Boole\", \"1815\", \"Boolean algebra\", \"English\"",
    "insert into scientists values \"Ernest\", \"Rutherford\", \"1871\", \"Nuclear physics\", \"New Zealander\"",
    "insert into scientists values \"Edwin\", \"Hubble\", \"1889\", \"Expanding universe\", \"American\"",
    "insert into scientists values \"Wilhelm\", \"Rontgen\", \"1845\", \"Xrays\", \"German\"",
    "insert into scientists values \"Paul\", \"Dirac\", \"1902\", \"Quantum mechanics\", \"English\"",
    "insert into scientists values \"Robert\", \"Oppenheimer\", \"1904\", \"Atomic bomb\", \"American\"",
    "insert into scientists values \"Linus\", \"Pauling\", \"1901\", \"Chemical bonding\", \"American\"",
    "insert into scientists values \"Srinivasa\", \"Ramanujan\", \"1887\", \"Mathematics\", \"Indian\"",
    "insert into scientists values \"Emmy\", \"Noether\", \"1882\", \"Abstract algebra\", \"German\"",
    "insert into scientists values \"Mary\", \"Anning\", \"1799\", \"Paleontology\", \"English\"",
    "insert into scientists values \"Florence\", \"Nightingale\", \"1820\", \"Nursing\", \"English\"",
    "insert into scientists values \"Rachel\", \"Carson\", \"1907\", \"Environmental science\", \"American\"",
    "insert into scientists values \"Jane\", \"Goodall\", \"1934\", \"Primatology\", \"English\"",
    "insert into scientists values \"Barbara\", \"McClintock\", \"1902\", \"Genetics\", \"American\"",
    "insert into scientists values \"Dorothy\", \"Hodgkin\", \"1910\", \"Xray crystallography\", \"English\"",
    "insert into scientists values \"ChienShiung\", \"Wu\", \"1912\", \"Nuclear physics\", \"Chinese\"",
    "insert into scientists values \"Katherine\", \"Johnson\", \"1918\", \"Spaceflight calculations\", \"American\"",
    "insert into scientists values \"Mae\", \"Jemison\", \"1956\", \"Astronaut\", \"American\"",
    "insert into scientists values \"Valentina\", \"Tereshkova\", \"1937\", \"Cosmonaut\", \"Russian\"",
    "insert into scientists values \"Sally\", \"Ride\", \"1951\", \"Astronaut\", \"American\"",
    "insert into scientists values \"Hypatia\", \"of Alexandria\", \"0360\", \"Philosophy\", \"Greek\""
  };
  SQL sql;
  Table t;
  string command;
  bool end = false;
  sql.batch();
  while(!end){
    getline(cin, command);
    if(command == "end")
      end = true;
    else{
        cout << sql.command(command) << endl << endl;
        cout << "RECORD NUMBERS: " << sql.select_recnos() << endl << endl;
    }
    sql.printOpenFiles();
  }
  return true;
}

TEST(TEST_STUB, TestStub) {
  // EXPECT_EQ(1, test_stub(false));
  EXPECT_EQ(1, test_interactive(false));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

  // for(int i = 0; i < commandList.size(); i++){
  //   sql.command(commandList.at(i));
  // }
  // cout << sql.command("select * from scientists");
  // cout << sql.command("select FIRST, YEAR from scientists where ((FIRST >= Aa and FIRST <= Az) or (FIRST >= AA and FIRST <= AZ))");
  // cout << sql.command("select FIRST, YEAR from scientists where FIRST >= Aa and FIRST <= Az or FIRST >= AA and FIRST <= AZ");
  // cout << sql.command("select * from scientists where NATIONALITY = English and LAST >= R or NATIONALITY = Italian and YEAR < 1500 or NATIONALITY = German and YEAR > 1900");
  
  //MISC. TEST CASES ***************
  // select * from scientists where FIRST < P or LAST < P or NATIONALITY = Italian and LAST = "da Vinci"
  //
  // select * from scientists where LAST > L and NATIONALITY = English or INVENTION = "Chemical bonding" or INVENTION = "Atomic bomb" or INVENTION = "Light bulb"
  // select * from scientists where INVENTION = "Chemical bonding" or INVENTION = "Atomic bomb" or INVENTION = "Light bulb" or LAST > L and NATIONALITY = English
  // select * from scientists where INVENTION = "Chemical bonding" or LAST > L and NATIONALITY = English or INVENTION = "Atomic bomb" or INVENTION = "Light bulb"

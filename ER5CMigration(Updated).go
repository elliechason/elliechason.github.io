//NOTE: This program was made by Elizabeth Chason and Cole Mathes under the Jefferson Lab High School Summer Honors Program 

package main

import (
	"database/sql"
	"flag"
	"fmt"
	_ "github.com/godror/godror"
)

type instantiation struct {
	ModUser      string
	ModDate      string
	TravRevision string
	TravSeqNum   int
	TravComplete string
	TravCloseWho string
	OBS          string
	TravId       string
	D3ID         string
	NCRID        string
	TravOpenDate string
	TravCloseDate string
	TravOpenWho   string
}


func check(err error){
	if err != nil {
		fmt.Println(err)
		panic(err)
	}
}
//TRAVELER@//pansophydb.jlab.org:1521/traveler.jlab
func main(){
	userPtr := flag.String("user", "false", "user")
	passwdPtr := flag.String("pass", "false", "password")

	flag.Parse()
	fmt.Println("ER5CMigration\nBy: Elizabeth Chason and Cole Mathes")
	db, err := sql.Open("godror", fmt.Sprintf(`user="%v" password="%v" connectString="%v"`, *userPtr, *passwdPtr, "TRAVELER@//pansophydb.jlab.org:1521/traveler.jlab"))
	check(err)
	defer func(db *sql.DB) {
		err := db.Close()
		if err != nil {

		}
	}(db)
	fmt.Println("Enter number of tables to be merged into ER5C table: ")
	var numTables int
	_, err = fmt.Scanln(&numTables)
	check(err)
	tableNames := make([]string, numTables)
	er5ctable := new(string)
	fmt.Println("Enter the TRAV_ID value.")
	for i, _ := range tableNames {
		_, err = fmt.Scanln(&tableNames[i])
	}
	fmt.Println("Enter ER5C TRAV_ID value.")
	_, err = fmt.Scanln(er5ctable)
	fmt.Println(tableNames, numTables, er5ctable)
	check(db.Ping())
	rows := make([]*sql.Rows, numTables)
	for i, _ := range tableNames {
		rows[i], err = retrieveOwnersData(db, *er5ctable, tableNames[i])
		check(err)
	}
	allTravInstantiations := make([][]instantiation, numTables)
	for i, val := range rows {
		allTravInstantiations[i] = make([]instantiation, 0)
		for val.Next() {
			allTravInstantiations[i] = append(allTravInstantiations[i], *new(instantiation))
			check(val.Scan(
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].ModUser,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].ModDate,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravRevision,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravSeqNum,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravComplete,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravCloseWho,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].OBS,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravId,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].D3ID,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].NCRID,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravOpenDate,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravCloseDate,
				&allTravInstantiations[i][len(allTravInstantiations[i])-1].TravOpenWho))
			allTravInstantiations[i][len(allTravInstantiations[i])-1].TravId = *er5ctable
		}
	}
	runningSum := 0
	for i, _ := range allTravInstantiations {
		runningSum += len(allTravInstantiations[i])
		for n, _ := range allTravInstantiations[i] {
			allTravInstantiations[i][n].TravSeqNum += runningSum
		}
	}
	for i, _ := range allTravInstantiations {
		for n, _ := range allTravInstantiations[i] {
			check(setOwnersData(db, allTravInstantiations[i][n]))
		}
	}
	check(setConfigData(db, runningSum, *er5ctable,))
	for _, val := range tableNames {
		_, err = getDataToMigrate(db, val, *er5ctable)
	}
}

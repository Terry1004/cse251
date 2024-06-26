#/bin/bash

folder="$1"
target="$2"

run_step() {
    make ./steps/$1/$2.o
    ./steps/$1/$2.o ${@:3}
}

case $folder in
    step-1)
        run_step $folder myhello;;
    step-2)
        run_step $folder rlc;;
    step-3)
        run_step $folder tax;;
    step-5)
        run_step $folder moon;;
    step-7)
        run_step $folder quadratic;;
    step-4 | step-6 | step-8 | step-11)
        # step-4: factorial, sine
        # step-6: combi, combi1, war
        # step-8: array, words
        # step-11: wumpus1, wumpus2
        run_step $folder $target;;
    step-9)
        if [ "$target" == "reverser" ]
        then
            run_step $folder reverser ${@:3}
        else
            run_step $folder $target
        fi;;
    step-10)
        cd ./steps/step-10
        case $target in
            "") docker compose run --build cse251 /bin/bash -c "make garage64 && ./garage";;
            reference) docker compose run --build cse251 ./garage-solution64;;
            debug) docker compose up --build -d;;
            clean) 
                cd ./Garage
                make clean;;
        esac;;
    step-12)
        cd ./steps/step-12
        case $target in
        "")
            make
            ./hanoi;;
        clean)
            make clean;;
        submit)
            make clean
            cd ../..
            tar cvzf hanoi.tar.gz ./steps/step-12;;
        esac;;
    step-13)
        cd ./steps/step-13
        case $target in
        "")
            make
            ./transistors;;
        clean)
            make clean;;
        submit)
            make clean
            cd ../..
            tar cvzf transistors.tar.gz ./steps/step-13;;
        esac;;
    step-14)
        cd ./steps/step-14
        case $target in
            "") docker compose run --build cse251 /bin/bash -c "make robot64 && ./robot";;
            debug) docker compose up --build -d;;
            clean)
                cd ./Robot
                make clean;;
        esac;;
    project-1)
        make ./projects/project-1/proj1.o
        ./projects/project-1/proj1.o;;
    project-2)
        cd ./projects/project-2
        case $target in
            "") docker compose run --build cse251 /bin/bash -c "make elevator64 && ./elevator";;
            reference) docker compose run --build cse251 ./elevator-solution-64;;
            eval-speed) docker compose run --build cse251 make elevator64-eval-speed;;
            debug) docker compose up --build -d;;
            clean)
                cd ./Elevator
                make clean;;
        esac;;
    project-3)
        cd ./projects/project-3
        case $target in
        "")
            make
            ./scheduler;;
        clean)
            make clean;;
        submit)
            make clean
            cd ../..
            tar cvzf scheduler.tar.gz ./projects/project-3;;
        esac;;
esac
